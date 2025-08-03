//Mafora Kesaobaka
//43031072
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Define a struct to store staff information
struct staff
{
    string name, surname;
    int staffNum;
    char Gender;
};

// A function to store staff data in a file
void storeData(fstream &staffFile, staff *members, int Capacity, int storage) // Use pointer to pass the array of staff
{
    if(storage <= 0)
    {
        cout << "\nPlease Enter a positive number: ";
        cin >> storage;
    }
    else
    {
        for(int i = 0; i < storage; i++)
        {
            // Use pointer arithmetic to access the name, the surname, the staff id number and the Gender.
            cout << "\nPlease enter names: ";
            cin.ignore();
            getline(cin, (members + i)->name);

            cout << "Please enter surname: ";
            cin >> (members + i)->surname;

            cout << "Please enter staff number: ";
            cin >> (members + i)->staffNum;

            cout << "Please enter gender type: ";
            cin >> (members + i)->Gender;
        }

        staffFile.open("StaffData.txt", ios::app);

        if (!staffFile) {
           cerr << "Unable to open file StaffData";
           exit(1);
           }

        for(int j = 0; j < storage; j++)
        {
            staffFile << (members + j)->name
                      << " " << (members + j)->surname
                      << " " << (members + j)->Gender
                      << " " << (members + j)->staffNum << endl;
        }

        staffFile.close();
        //available += storage;
    //cout << available << endl;
        cout << "Request complete" << endl;
    }


}

// A function to remove a staff from the array and update the file
int removeStaff(fstream &staffFile, staff *members, int Capacity, int position, int available) // Use pointer to pass the array of staff
{

    for(int i = position; i < available; i++)
    {
        // Use pointer arithmetic to access and assign the name, the surname, the staff id number and the Gender.
        (members + i - 1)->name = (members + i)->name;
        (members + i - 1)->surname = (members + i)->surname;
        (members + i - 1)->Gender = (members + i)->Gender;
        (members + i - 1)->staffNum = (members + i)->staffNum;
    }
    available--;

    //cout << available << endl;

    staffFile.open("StaffData.txt", ios::out);

    if(!staffFile)
    {
        cerr << "Unable to open the file" << endl;
        return 1;
    }

    for(int j = 0; j < available; j++)
        {
            // Use pointer arithmetic to access the name, the surname, the staff id number and the Gender.
            staffFile << (members + j)->name
                      << " " << (members + j)->surname
                      << " " << (members + j)->Gender
                      << " " << (members + j)->staffNum << endl;
        }
    staffFile.close();

    cout << "Request complete " << endl;
}

// A function to display staff data from the file
void displayData(fstream &staffFile, staff *members, int Capacity, int available) // Use pointer to pass the array of staff
{
    staffFile.open("StaffData.txt", ios::in);

   // Check if the file was successfully opened
   if (!staffFile) {
       cerr << "Unable to open file StaffData";
       exit(1);
   }

   int i = 0;
   while(staffFile.good() || i < available)
   {
       staffFile >> (members + i)->name >> (members + i)->surname >> (members + i)->Gender >> (members + i)->staffNum; // Use pointer arithmetic to read data into fields
       cout << (i + 1) << " "
            << (members + i)->name << " "
            << (members + i)->surname << " "
            << (members + i)->Gender << " "
            << (members + i)->staffNum << endl; // Use pointer arithmetic to display data from fields
        i++;
   }
   staffFile.close();
}

// A function to check if a staff is allowed to enter the facilities
void CheckingStaff(fstream &staffFile, staff *members, int Capacity) // Use pointer to pass the array of staff
{
   staffFile.open("StaffData.txt", ios::in);

   // Check if the file was successfully opened
   if (!staffFile) {
       cerr << "Unable to open file StaffData";
       exit(1);
   }

   int i = 0;
   while(staffFile.good() && i < Capacity)
   {
       staffFile >> (members + i)->name >> (members + i)->surname >> (members + i)->Gender >> (members + i)->staffNum; // Use pointer arithmetic to read data into fields
       //Uncomment this part to display the data on the console
       /*cout << (members + i)->name << " "
            << (members + i)->surname << " "
            << (members + i)->Gender << " "
            << (members + i)->staffNum << endl;*/ // Use pointer arithmetic to display data from fields
        i++;
   }

    staff user;

   while(Capacity <= 50 || user.staffNum == '\0')
   {
       staff user;

       cout << "\nEnter your staff number please(NB the staff number must not contain characters): ";
       cin >> user.staffNum;

        if(user.staffNum == '\0')
            break;
       cout << "\nEnter your names: ";
       cin.ignore(); // Ignore the newline character left in the buffer by cin
       getline(cin, user.name);

       cout << "Enter your surname: ";
       cin >> user.surname;

       cout << "Enter your gender: ";
       cin >> user.Gender;

       bool found = false;
       for (int j = 0; j < i; j++) {
            // Use pointer arithmetic to compare the staffNum field, name field, surname field and Gender field
           if ((members + j)->staffNum == user.staffNum &&
               (members + j)->name == user.name &&
               (members + j)->surname == user.surname &&
               (members + j)->Gender == user.Gender) {
               found = true;
               break;
           }
       }

       if (!found) {
           cout << "You are not allowed to enter this facilities!!! " << endl;
       } else {
           cout << "Welcome " << user.name << endl;
           Capacity--;
       }

   }

   staffFile.close();
}

int main()
{
    const int Capacity = 50; // Define a constant for the maximum capacity of the array
    int available = 10; // Define a variable for the available slots in the array
    int storage = 0; // Define a variable for the number of staff to be added
    int choice, position, attempt = 3;// Define variables for the user's choice and position
    string adminName, adminPassword, adminSurname;
    string option,option2, password;
    bool Opt1 = false, Opt2 = false;

    cout << "Welcome, please create password if you are the admin\n" << endl;

    cout << "Are you the admin?(Yes or No): ";
    cin >> option;
    cout << endl;
    //this portion of code check if the first person to check the program is the admin and it wait until the admin get access
    while(option != "yes" && option != "Yes" && option != "YES")
    {
        cout << "This require the admin for setup!!! " << endl;
        cout << "\n\nAre you the admin?(Yes or No): ";
        cin >> option;
    }
    // this portion gets the admins choices/decisions  about the program
    // this include checking if the admin want to create password for certain lines of conditions on the program
    if(option == "yes" || option == "Yes" || option == "YES")
    {
        Opt1 = true;
        cout << "\nWill you like to create a password to avoid data change by others(Yes or No): ";
        cin >> option2;

        if(option2 != "yes" && option2 != "Yes" && option2 != "YES")
        {
            cout << "\nNote that everyone can have access to the staff data and manipulate the data." << endl;
            cout << " Not creating a password... \n\n" << endl;
            Opt2 = false;
        }
        //collecting the admin information and password to store in a file
        else
        {
            Opt2 = true;
            cout << "\nEnter your names: ";
            cin >> adminName;

            cout << "Enter your surname: ";
            cin >> adminSurname;

            cout << "Create a strong password: ";
            cin >> adminPassword;
            ofstream adminFile;

            adminFile.open("adminData.txt", ios::out);

            if(adminFile.is_open())
            {
                adminFile << adminName << " "
                          << adminSurname << " "
                          << adminPassword << endl;
            }
            adminFile.close();
            cout << "Done." << endl;
        }
    }


    staff *members = new staff[Capacity]; // Dynamically allocate an array of staff using pointer

    fstream staffFile; // Define a file stream object

bool repeat = true;
//this part is for decisions made by the admin, conditional statements will direct the the option selected to the right block of code to be executed
    if(Opt1 == true && Opt2 == false)
           {
                cout <<"====================================================" << endl;
                cout << "___________Welcome to Primitive offices___________" << endl;
                cout <<"====================================================" << endl;

                cout << "\nPlease select one of the choices below" << endl;

                cout << "\n1. Add new staff members." << endl;
                cout << "2. Remove a staff member and display staff data after removing a member " << endl;
                cout << "3. Run Program to check if staff members are allowed to enter. " << endl;
                cout << "4. Add new members and run Program to check if staff members are allowed to enter." << endl;
                cout << "5. Display staff data." << endl;
                cout << "6. Exit." << endl;

                cout << "\nEnter your choice: ";
                cin >> choice;
// This block of code is not protected with a password
                while(repeat && Capacity != 0)
                {
                        switch(choice)
                    {
                        case 1:
                            cout << "\nEnter the number (Positive integer) of staff to add to workers database: ";
                            cin >> storage;
                            available +=  storage;
                            storeData(staffFile, members,Capacity, storage); // Call storeData function with pointer as argument
                            break;

                        case 2:
                            displayData(staffFile, members, Capacity, available); // Call displayData function with pointer as argument
                            cout << "\nThis option is for removing staff members, " << endl
                                 << "from the given list please choose the number of the staff you will like to remove: ";
                            cin >> position;
                            removeStaff(staffFile, members,Capacity, position, available); // Call removeStaff function with pointer as argument
                            available--;
                            break;
                        case 3:
                            CheckingStaff(staffFile, members, Capacity);
                            break;

                        case 4:
                            storeData(staffFile, members,Capacity, storage);
                            CheckingStaff(staffFile, members,Capacity);
                            break;

                        case 5:
                            displayData(staffFile, members, Capacity, available);
                            break;
                        case 6:
                            cout << "Exiting the program..." << endl;
                            break;

                        default:
                            cout << "You selected wrong choice." << endl;
                            break;
                    }
                    cout << "\n1. Add new staff members." << endl;
                    cout << "2. Remove a staff member and display staff data after removing a member " << endl;
                    cout << "3. Run Program to check if staff members are allowed to enter. " << endl;
                    cout << "4. Add new members and run Program to check if staff members are allowed to enter." << endl;
                    cout << "5. Display staff data." << endl;
                    cout << "6. Exit." << endl;

                    cout << "\nEnter your choice: ";
                    cin >> choice;
                }
           }
           //this block of code is protected by the admin password
           else if(Opt1 == true && Opt2 == true)
           {
                    cout <<"====================================================" << endl;
                    cout << "___________Welcome to Primitive offices___________" << endl;
                    cout <<"====================================================" << endl;

                    cout << "\nPlease select one of the choices below" << endl;

                    cout << "\n1. Add new staff members." << endl;
                    cout << "2. Remove a staff member and display staff data after removing a member " << endl;
                    cout << "3. Run Program to check if staff members are allowed to enter. " << endl;
                    cout << "4. Add new members and run Program to check if staff members are allowed to enter." << endl;
                    cout << "5. Display staff data." << endl;
                    cout << "6. Exit." << endl;

                    cout << "\nEnter your choice: ";
                    cin >> choice;

                    while(repeat && Capacity != 0)
                    {
                            switch(choice)
                        {
                            case 1:
                                   cout << "This site require admin password. \nPlease enter your password: ";
                                   cin >> password;
                                   while(password != adminPassword && attempt != 0)
                                   {
                                       cout << "\nIncorrect password, please try again.\nYou are left with " << attempt << " attempt(s): ";
                                       cin >> password;
                                       attempt--;
                                   }
                                   if(attempt == 0)
                                   {
                                       cout << "You entered incorrect password three times, try again after one month. " << endl;
                                   }

                                   else if(password == adminPassword)
                                   {
                                        cout << "\nEnter the number (Positive integer) of staff to add to workers database: ";
                                        cin >> storage;
                                        available +=  storage;
                                        storeData(staffFile, members,Capacity, storage); // Call storeData function with pointer as argument
                                   }
                                   else
                                   {
                                       cout << "??" << endl;
                                       cout << "..." << endl;
                                   }
                                break;

                            case 2:
                                   cout << "\nThis site require admin password. \nPlease enter your password: ";
                                   cin >> password;
                                   while(password != adminPassword && attempt != 0)
                                   {
                                       cout << "\nIncorrect password, please try again.\nYou are left with " << attempt << " attempt(s): ";
                                       cin >> password;
                                       attempt--;
                                   }
                                   if(attempt == 0)
                                   {
                                       cout << "You entered incorrect password three times, try again after one month. " << endl;
                                   }

                                   else if(password == adminPassword)
                                   {
                                       cout << endl;
                                        displayData(staffFile, members, Capacity, available); // Call displayData function with pointer as argument
                                        cout << "\nThis option is for removing staff members, " << endl
                                             << "from the given list please choose the number of the staff you will like to remove: ";
                                        cin >> position;
                                        removeStaff(staffFile, members,Capacity, position, available); // Call removeStaff function with pointer as argument
                                        available--;
                                   }
                                   else
                                   {
                                       cout << "??" << endl;
                                       cout << "..." << endl;
                                   }
                                break;
                            case 3:
                                CheckingStaff(staffFile, members, Capacity);
                                break;
                            case 4:
                                storeData(staffFile, members,Capacity, storage);
                                CheckingStaff(staffFile, members,Capacity);
                                break;
                            case 5:
                                 cout << "\nThis site require admin password. \nPlease enter your password: ";
                                   cin >> password;
                                   while(password != adminPassword && attempt != 0)
                                   {
                                       cout << "\nIncorrect password, please try again.\nYou are left with " << attempt << " attempt(s): ";
                                       cin >> password;
                                       attempt--;
                                   }
                                   if(attempt == 0)
                                   {
                                       cout << "You entered incorrect password three times, try again after one month. " << endl;
                                   }

                                   else if(password == adminPassword)
                                   {
                                       displayData(staffFile, members, Capacity, available);
                                   }
                                   else
                                   {
                                       cout << "??" << endl;
                                       cout << "..." << endl;
                                   }
                                break;
                            case 6:
                                cout << "Exiting the program..." << endl;
                                break;

                            default:
                                cout << "You selected wrong choice." << endl;
                                break;
                        }
                        cout << "\n1. Add new staff members." << endl;
                        cout << "2. Remove a staff member and display staff data after removing a member " << endl;
                        cout << "3. Run Program to check if staff members are allowed to enter. " << endl;
                        cout << "4. Add new members and run Program to check if staff members are allowed to enter." << endl;
                        cout << "5. Display staff data." << endl;
                        cout << "6. Exit." << endl;

                        cout << "\nEnter your choice: ";
                        cin >> choice;
                    }
           }
    return 0;

}
/*Kesaobaka Mafora M 43031072
Dbayne Rakate M 31425166
Realeboga Kokome F 45120415
Segadile Skomota F 43125014
Temo Mogoma M 32564102
Katlego Pula F 21546524
Kebabone Kemang M 32154685
Kearabilwe Moatshe F 41250124
Relebetswe Kweneng M 35641203
Rapula MonnaRula M 24513558*/
