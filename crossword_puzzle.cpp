#include <iostream>
#include <chrono>
#include <malloc.h>

using namespace std;


struct node   //defining the structure of puzzle
{
    char data;
    struct node *right;
    struct node *bottom;
    struct node *cross;
};

struct node *insert_end(struct node *start, char data);

struct node *insert_end(struct node *start_fun, char data)
{
    struct node *ptr, *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node -> data =  data;
    new_node -> right = NULL;
    new_node -> bottom = NULL;
    new_node -> cross = NULL;
    ptr = start_fun;
    while(ptr -> right != NULL)
    {
        ptr = ptr -> right;
    }
    ptr -> right = new_node;
    return start_fun;
}

class Puzzle
{
    public:
        char name[50];
        int pSize;
        struct node *start;
        char question[20][100];
        int solution[20][3];

    public:
        Puzzle()     //initializing the initial puzzle to be null
        {
            struct node *new_node;
            new_node = (struct node *)malloc(sizeof(struct node));
            new_node -> right = NULL;
            new_node -> bottom = NULL;
            new_node -> cross = NULL;
            start = new_node;
        }
        void getName()
        {
            cout<<"Enter the name of the puzzle:";
            cin.get(name,50);
        }
        void getDimension()
        {
            cout<<"Enter the size of the puzzle:";
            cin>>pSize;
        }
        struct node *makePuzzle()
        {
            int i,j;
            char data;
            struct node *temp_start, *new_node;
            temp_start = start;
            cout<<"\nAdd the data for the puzzle.\n\n";
            cout<<"INSTRUCTIONS:\n\n";
            cout<<"Step 1: Get the data you wish to add ready on a piece of paper.\n\n";
            cout<<"Step 2: You are expected to add in a row wise order. So, add the data of one row completely and then only move to the next.\n\n";
            cout<<"And here you begin....\n\n";

            for(i=1 ; i<=pSize ; i++)
            {
                j=1;
                cout<<"Enter data for element of row "<<i<<" and column "<<j<<":";
                cin>>data;
                start -> data = data;
                start -> right = NULL;
                start -> bottom = NULL;
                start -> cross = NULL;
                for(j=2 ; j<=pSize ; j++)
                {
                    cout<<"Enter data for element of row "<<i<<" and column "<<j<<":";
                    cin>>data;
                    start = insert_end(start, data);
                }
                if( i != pSize)
                {
                    new_node = (struct node *)malloc(sizeof(struct node));
                    start -> bottom = new_node;
                    start = new_node;
                }
            }
            start = temp_start;
            return start;
        }

        struct node *setBottomLinks()
        {
            struct node *right_worker, *bottom_worker, *chk, *bottom_worker_instance;
            right_worker = start;
            bottom_worker = start;
            chk = start;
            bottom_worker_instance = start;

            while(chk -> bottom != NULL)
            {
                chk = chk -> bottom;
                right_worker = bottom_worker_instance -> right;
                bottom_worker = chk;
                bottom_worker_instance = bottom_worker;

                while(bottom_worker -> right != NULL)
                {
                    bottom_worker = bottom_worker -> right;
                    right_worker -> bottom = bottom_worker;

                    if(right_worker -> right != NULL)
                    {
                        right_worker = right_worker -> right;
                    }
                }
            }
            return start;
        }

        struct node *setMiddleCrossLinks()
        {
            struct node *instance, *bottom_worker, *to_add;
            int chk = 1;
            int n;
            instance = start;
            bottom_worker = start;
            to_add = start;
            while(chk < pSize)
            {
                instance = instance -> bottom;
                bottom_worker = instance;
                n = 1;

                while(n <= chk)
                {
                    bottom_worker = bottom_worker -> right;
                    n++;
                }
                to_add -> cross = bottom_worker;
                to_add = bottom_worker;
                chk++;
            }
            return start;
        }

        struct node *setUpperTriangularLinks()
        {
           struct node *bottom_worker, *temp_right_worker, *right_worker;
           temp_right_worker = start -> right;
           while(temp_right_worker -> right != NULL)
           {
               right_worker = temp_right_worker;
               bottom_worker = right_worker -> bottom -> right;
               right_worker -> cross = bottom_worker;

               while(bottom_worker -> right != NULL)
               {
                   right_worker = bottom_worker;
                   bottom_worker = bottom_worker -> bottom -> right;
                   right_worker -> cross = bottom_worker;
               }
               temp_right_worker = temp_right_worker -> right;
           }
           return start;
        }

        struct node *setLowerTriangularLinks()
        {
           struct node *bottom_worker, *temp_bottom_worker, *right_worker;
           temp_bottom_worker = start -> bottom;
           while(temp_bottom_worker -> bottom != NULL)
           {
               bottom_worker = temp_bottom_worker;
               right_worker = bottom_worker -> bottom -> right;
               bottom_worker -> cross = right_worker;

               while(right_worker -> bottom != NULL)
               {
                   bottom_worker = right_worker;
                   right_worker = right_worker -> bottom -> right;
                   bottom_worker -> cross = right_worker;
               }
               temp_bottom_worker = temp_bottom_worker -> bottom;
           }
           return start;
        }

        struct node *displayPuzzle()
        {
            struct node *temp_start, *start_1;
            temp_start = start;
            int i;
            cout<<"\nThe puzzle entered is:\n";
            i = pSize;
            while(i >= 1)
            {
                start_1 = start;
                while(start_1 != NULL)
                {
                    cout<<start_1 -> data<<" ";
                    start_1 = start_1 -> right;
                }
                cout<<"\n";
                start = start -> bottom;
                i--;
            }
            start = temp_start;
            return start;
        }

        void getQuestionAndSolution()
        {
            int n,i;
            cout<<"\nEnter the number of questions you wish to add:";
            cin>>n;
            cout<<"\nFollow the steps given below:"
            <<"\n\nStep 1: Add the question."
            <<"\n\nStep 2: Number the nodes on the piece of paper on which you have the puzzle."
            <<"\n\tNumber the first row and first column element as 1 and increment as you move row-wise."
            <<"\n\tOnce a particular row is complete, move to the next row and continue the numbering. Follow this till the last element."
            <<"\n\tEg:- In a 4X3 puzzle, i.e. puzzle[4][3], puzzle[0][0] is numbered as 1, puzzle[0][1] as 2, puzzle[1][0] as 4 and so on."
            <<"\n\tThe number added to the node is called as INDEX of that node"
            <<"\n\nStep 3: The solution would contain 3 space separated integers. \n\t1st integer: INDEX of the starting position of the solution. \n\t"
            <<"2nd integer: Direction of solution (1=Row-wise, 2=Cross, 3=Column-wise)\n\t"
            <<"3rd integer: Length of solution"

            <<"\n\nLet's begin!\n";

            char troubleshoot[20];
            /*
            This is just added to troubleshoot.
            Without this Question 1 was not getting accepted, due to the getline() function.
            The getline() function was accepting the '\n' or 'ENTER' pressed, for the Question 1 and thus enabling the user to input Qn.1
            */
            cin.getline(troubleshoot,20);

            for(i=1;i<=n;i++)
            {
                cout<<"\nEnter question "<<i<<":";
                cin.getline(question[i-1],100);
            }

            for(i=1;i<=n;i++)
            {
                cout<<"\nEnter solution "<<i<<":";
                cin>>solution[i-1][0]>>solution[i-1][1]>>solution[i-1][2];
            }

            cout<<"FINAL LIST:\n";

            for(i=1;i<=n;i++)
            {
                cout<<"\nQuestion "<<i<<":"<<question[i-1];
                cout<<"\nAnswer "<<i<<":"<<solution[i-1][0]<<" "<<solution[i-1][1]<<" "<<solution[i-1][2];
            }

        }
};

int main()
{
    using namespace std::chrono;
    Puzzle p;
    struct node *start_main;
    p.getName();
    p.getDimension();
    start_main = p.start;
    
    milliseconds mil(1000);
    mil = mil*60;
    start_main = p.makePuzzle();
    start_main = p.setBottomLinks();
    start_main = p.setMiddleCrossLinks();
    start_main = p.setUpperTriangularLinks();
    start_main = p.setLowerTriangularLinks();
    float ans = mil.count()/864002;

    
    start_main = p.displayPuzzle();
    p.getQuestionAndSolution(); 
    
    std::cout << "\n" << ans << " seconds.\n"; 

    return 0;
}
