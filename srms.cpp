#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class student{
    int rollno;
    char name[50];
    int eng_marks,math_marks,sci_marks,lang2_marks,cse_marks;
    double average;
    char grade;

    public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
};

void student::calculate(){
    average=(eng_marks+math_marks+sci_marks+lang2_marks+cse_marks)/5.0;
    if(average>=90)
        grade='A';
    else if (average>=75)
        grade='B';
    else if(average>=50)
        grade='C';
    else grade='F';
}

void student::getdata(){
    cout<<"\nenter student roll no.:";
    cin>>rollno;
    cout<<"\n\nenter student name:";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nall marks should be out of 100";
    cout<<"\nenter marks in english:";
    cin>>eng_marks;
    cout<<"\nenter marks in math:";
    cin>>math_marks;
    cout<<"\nenter marks in science:";
    cin>>sci_marks;
    cout<<"\nenter marks in lang2:";
    cin>>lang2_marks;
    cout<<"\nenter marks in cse:";
    cin>>cse_marks;
    calculate();
}

void student::showdata() const{
    cout<<"\nrollno of student:"<<rollno;
    cout<<"\nname of students:"<<name;
    cout<<"\nenglish:"<<eng_marks;
    cout<<"\nmaths:"<<math_marks;
    cout<<"\nscience:"<<sci_marks;
    cout<<"\nlang2:"<<lang2_marks;
    cout<<"\ncse:"<<cse_marks;
    cout<<"\naverage marks:"<<average;
    cout<<"\ngrade of students:"<<grade;
}

int student::retrollno() const{
    return rollno;
}

void  create_student();
void display_sp(int);
void display_all();
void delete_student(int);
void change_student(int);

int main(){
    char ch;
    cout<<setprecision(2);
    do{
        char ch;
        int num;
        system("cls");
        cout<<"\n\n\n\tmenu";
        cout<<"\n\n\n\t1.create student record";
        cout<<"\n\n\t2.search student record";
        cout<<"\n\n\t3.display all sudennt records";
        cout<<"\n\n\t4.delete  student records";
        cout<<"\n\n\t5.modify student records";
        cout<<"\n\n\t6.exit";
        cout<<"\n\n\twhat is your choice(1/2/3/4/5/6):";
        cin>>ch;
        system("cls");
        switch(ch){
            case '1': create_student(); break;
            case '2': cout<<"\n\n\tenter the rollno:";
            cin>>num;
            display_sp(num);break;
            case '3': display_all(); break;
            case '4': cout<< "\n\n\tenter the rollno:";
            cin>>num;
            delete_student(num);break;
            case '5' : cout<<"\n\n\tenter the rollno ";
            cin>>num;
            change_student(num);break;
            case '6': cout<<"exiting ! thhank you.";
            exit(0);
        }
    }
    while(ch!='6');
    return 0;
}
void create_student(){
    student stud;
    ofstream oFile;
    oFile.open("student.dat",ios::binary|ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char*>(&stud),sizeof(student));
    oFile.close();
    cout<<"\n\nstudent record hass been created.";
    cin.ignore();
    cin.get();
}

void display_all(){
    student stud;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile){
        cout<<"file could not be opened!! press any keyto exit.";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\tdisplaying all records\n\n";
    while(infile.read(reinterpret_cast<char*>(&stud),sizeof(student))){
        stud.showdata();
        cout<<"\n\n____________________\n";
    }
    infile.close();
    cin.ignore();
    cin.get();
}
void display_sp(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile){
        cout<<"file could not be opened.....press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char*>(&stud),sizeof(student))){
        if (stud.retrollno()==n){
            stud.showdata();
            flag=true;
        }
    }
    iFile.close();
    if(flag==false)
    cout<<"\n\nrecord does not exit";
    cin.ignore();
    cin.get();
}

void change_student(int n){
    bool found=false;
    student stud;
    fstream f1;
    f1.open("student.dat",ios::binary|ios::in|ios::out);
    if(!f1){
        cout<<"file could not be opened.press any key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    while(!f1.eof() && found==false){
        f1.read(reinterpret_cast<char *>(&stud),sizeof(student));
        if(stud.retrollno()==n){
            stud.showdata();
            cout<<"\nenter new student details:"<<endl;
            stud.getdata();
            int pos=(-1)*static_cast<int>(sizeof(stud));
            f1.seekp(pos,ios::cur);
            f1.write(reinterpret_cast<char*>(&stud),sizeof(student));
            cout<<"\n\n\trecord update";
            found=true;
        }
    }
    //iFile.close();
    if(found==false)
        cout<<"\n\nrecord not found.";
        cin.ignore();
        cin.get();
}
void delete_student(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile){
        cout<<"file not opened...press any key";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream ofile;
    ofile.open("temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char*>(&stud),sizeof(student))){
        if(stud.retrollno()!=n){
            ofile.write(reinterpret_cast<char*>(&stud),sizeof(student));
        }
    }
    ofile.close();
    iFile.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    cout<<"\n\n\trecord deleted..";
    cin.ignore();
    cin.get();
}
