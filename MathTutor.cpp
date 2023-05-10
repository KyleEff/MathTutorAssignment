/*
    Kyle Free
    COSC 1436 - Programming Fundamentals I
    4/11/23
    Math Tutor

    This program demonstrates the proper use of logic and decision structures.
    The User object is created, and then that object runs a menu that creates an
        Add or Subtract object depending on the operation that the user wishes to perform.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

namespace WeekFourAssignment {
    // Interface class that adds utility for the Add and Subtract classes
    class IUtility {
        public:
        virtual double Calculate() = 0;
        virtual void Print() = 0;
        virtual double GetAnswer() = 0;
    };

    // The Add class generates two operands between 1 and 500,
    //  and then performs an addition operation
    class Add : public IUtility {
        // Attributes
        vector<int> operands;
        int answer; // The answer to the equation

        // Constructor
        public:
        Add() :
            answer(0) {
                // Seed the random number generator with the system time
                srand(time(nullptr));
                // Push random operands onto the vector
                for (auto i{0}; i < 2; i++) 
                    operands.push_back(rand() % 500);
                // Run the calculation
                Calculate();
        }
        /*
        Add(vector<T> operands) :
            operands(operands),
            answer(0.0)
                { Calculate(); }
        */

        // Calculate() adds the operands to the answer integer
        double Calculate() {

            for (auto num : operands) 
                answer += num;
            
            return answer;
        }

        // Print() displays the equation
        void Print()
            { cout << operands[0] << " + " << operands[1] << " = "; }

        // GetAnswer() returns only the answer variable
        double GetAnswer()
            { return answer; }
    };

    // The Subtract class generates two operands between 1 and 500,
    //  and then performs a subtraction operation
    class Subtract : public IUtility {
        // Attributes
        vector<int> operands;
        int answer; // The answer to the equation

        public:
        Subtract() :
            answer(0) {
                // Seed the random number generator with the system time
                srand(time(nullptr));
                // Push random operands onto the vector
                for (auto i{0}; i < 2; i++)
                    operands.push_back(rand() % 500);
                // Because this is subtract, the operands need a number to subtract from
                answer += operands[0];
                Calculate();
            }
        /*
        Subtract(vector<T> operands) :
            operands(operands),
            answer(operands[0])
                { Calculate(); }
        */

        // Calculate() subtracts the second operand from the answer integer, aka the first operand
        double Calculate() {

            answer -= operands[1];
            return answer;
        }

        // Print() displays the equation
        void Print()
            { cout << operands[0] << " - " << operands[1] << " = "; }

        // GetAnswer() returns only the answer variable
        double GetAnswer()
            { return answer; }

    };

    // The User class represents the user of the program interfacing with the Add and Subtract classes
    class User {
        // Attributes
        int answer; // This is the user's answer to the equation

        Add* add{ nullptr };
        Subtract* sub{ nullptr };

        // Constructor
        public:
        User()
            { Menu(); }

        // Destructor
        ~User() {
            // Delete pointer memory
            delete
                add,
                sub;

            // Clear out pointer addresses and reset answer variable
            add = nullptr;
            sub = nullptr;
            answer = 0;
        }

        // Menu() starts up the selection menu for the user to choose their operation
        void Menu() {

            int choice = 0; // This variable stores the user's choice
            
            // This loop runs the program as long as the user does not exit
            while (choice != 3) {

                cout
                    << "-----------------------------------\n"
                    << "Make your choice:\n"
                    << "1: Add\n"
                    << "2: Subtract\n"
                    << "3: Exit Program"
                    << endl;

                cin >> choice;

                // This switch statement directs the user's choice
                switch (choice) {

                    case 1: // add
                        add = new Add();
                        AskAnswer();
                        break;
                    
                    case 2: // subtract
                        sub = new Subtract();
                        AskAnswer();
                        break;
                    
                    default: // If any number other than 1 or 2 is entered, the program shuts down
                        choice = 3;
                        break;
                }
            }
        }

        // AskAnswer() prompts the user as to what their answer to the equation is
        void AskAnswer() {

            cout << "Please answer the following:" << endl;

            if (add != nullptr) // if there is an Add object, print the equation
                add->Print();
            else if (sub != nullptr) // if there is a Subtract object, print the equation
                sub->Print();

            // Input the user's answer
            cin >> this->answer;
            // Check the user's answer
            CheckAnswer();
        }

        // CheckAnswer() checks the user's answer against the actual answer of the equation
        void CheckAnswer() {

            if (add != nullptr)  // If there is an Add object
                add->GetAnswer() == this->answer ? // Check to see if the User and Add objects' answers match
                    cout << "You are correct!" << endl
                :
                    cout << "You are wrong. The answer is " << add->GetAnswer() << endl;
            
            if (sub != nullptr) // If there is a Subtract object
                sub->GetAnswer() == this->answer ? // Check to see if the User and Subtract objects' answers match
                    cout << "You are correct!" << endl
                :
                    cout << "You are wrong. The answer is " << sub->GetAnswer() << endl;

            // Destructor Call to clear out memory
            this->~User();
        }
    };
}

// Driver Function
int main() {
    /*
        srand(time(nullptr));
        int rand_int = rand() % 500;

        cout << rand_int << endl;
        

        vector<int> numbers = { 10, 15 };
        Add test(numbers);
        Subtract test(numbers);

        Add test;
        Subtract test;
        test.Print();
        cout << test.GetAnswer() << endl;
    */
    cout << "Welcome to the Math Tutor program!" << endl;
    WeekFourAssignment::User run; // Run the program

    return 0;
}
