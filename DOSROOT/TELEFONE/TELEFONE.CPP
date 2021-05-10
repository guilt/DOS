// Telephone and Address Organiser .
// Coded and Debbugged by Karthik Kumar V .

#include "fstream.h"
#include "string.h"
#include "process.h"
#include "stdio.h"
#include "conio.h"

// Maximum Number of records you can store .

#define MAX 150
#define TF "TELEFONE.DAT"

// Fixed Length Strings .
#define ALENGTH 41

int i, nrec;
fstream file;

// Hey ,I wrote this Useful Search Routine !
int strfind(char str1[ALENGTH], char str2[ALENGTH]) {
  int found = 0, l1 = 0, l2 = 0, i = 0, ml, k;
  for (; str1[l1] != 0; l1++)
    ;
  for (; str2[l2] != 0; l2++)
    ;
  if (l1 > l2) {
    return found;
  }
  for (i = 0; i <= (l2 - l1) && found == 0; i++) {
    if (str1[0] == str2[i]) {
      found = 1;
      if (l1 > 1) {
        for (k = 1; found != 0 && k < l1; k++) {
          if (str1[k] != str2[i + k]) {
            found = 0;
          }
        }
      }
    }
  }
  return found;
}

// This One Too .
int isndummytel(char str[ALENGTH]) {
  int cnt = 0, i = 0;
  for (; str[i] != 0; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      cnt++;
    }
  }
  return cnt;
}

class tele {
 public:
  // Maintain this Order Strictly ,for DataBasing .
  char telenumber[ALENGTH], name[ALENGTH], nname[ALENGTH], email[ALENGTH],
      add1[ALENGTH], add2[ALENGTH], city[ALENGTH], pincode[ALENGTH],
      state[ALENGTH], country[ALENGTH];
  tele() {
    telenumber[0] = name[0] = nname[0] = email[0] = add1[0] = add2[0] =
        city[0] = pincode[0] = state[0] = country[0] = 0;
  }
  void getdata();
  void putdata(int pflag = 0) {
    cout << "\n" << name;
    if (nname[0] != 0) {
      cout << " (aka) " << nname;
    }
    if (isndummytel(telenumber) || pflag) {
      cout << "\nNumber : [" << telenumber << "]";
    }
    if (email[0] != 0) {
      cout << "\nE-Mail/Web : <" << email << ">";
    }
    if (add1[0] != 0) {
      cout << "\n" << add1;
    }
    if (add2[0] != 0) {
      cout << "\n" << add2;
    }
    if (city[0] != 0) {
      cout << "\n" << city;
    }
    if (pincode[0] != 0) {
      if (city[0] != 0) {
        cout << " - ";
      } else {
        cout << "\n";
      }
      cout << pincode;
    }
    if (state[0] != 0) {
      cout << "\n" << state;
    }
    if (country[0] != 0) {
      cout << "\n" << country;
    }
    cout << "\n";
  }
} data[MAX];

void tele::getdata() {
  cout << "\nEnter Data :\n";
  do {
    cout << "Enter Name : ";
    gets(name);
  } while (name[0] == 0);
  cout << "Enter Nick Name : ";
  gets(nname);
  do {
    cout << "Enter Telephone Number : ";
    gets(telenumber);
  } while (telenumber[0] == 0);
  cout << "Enter E-Mail Address/Web Page : ";
  gets(email);
  cout << "Enter Address Line 1 : ";
  gets(add1);
  cout << "Enter Address Line 2 : ";
  gets(add2);
  cout << "Enter City : ";
  gets(city);
  cout << "Enter Zip/Pin Code : ";
  gets(pincode);
  cout << "Enter State : ";
  gets(state);
  cout << "Enter Country : ";
  gets(country);
}

// Used for Databasing at the end .
void dosort() {
  // Sort first by name ,then nickname .
  tele temp;
  int i, j;
  for (i = 0; i < nrec; i++) {
    for (j = 0; j < nrec - i - 1; j++) {
      if (strcmp(data[j].name, data[j + 1].name) > 0) {
        temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
      if (strcmp(data[j].name, data[j + 1].name) == 0 &&
          strcmp(data[j].nname, data[j + 1].nname) > 0) {
        temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
}

void init() {
  clrscr();
  file.open(TF, ios::in | ios::out | ios::binary);
  if (!file) {
    cout << "File Error !\n";
    exit(-1);
  }
  nrec = 0;
  if (file.get() != 'T' || file.get() != 'F') {
    // cout<<"Please wait ,file is just being created ....\n";
    file << "TF";
    file.write((char*)&nrec, sizeof(int));
    return;
  }
  file.read((char*)&nrec, sizeof(int));
  if (nrec > MAX) {
    cout << "More Records than I can Handle !\n";
    exit(-1);
  }
  if (nrec) {
    // cout<<"Please wait ,file is being read ....\n";
    for (i = 0; i < nrec; i++) {
      file.read((char*)&data[i], sizeof(tele));
    }
  }
}

void finish() {
  // cout<<"Please wait ,file is being written to ....\n";
  file.seekg(2, ios::beg);
  file.write((char*)&nrec, sizeof(int));
  dosort();
  for (i = 0; i < nrec; i++) {
    file.write((char*)&data[i], sizeof(tele));
  }
  file.close();
  clrscr();
  exit(0);
}

void findbyname() {
  char sstr[ALENGTH];
  cout << "\nEnter the Name to be Searched : ";
  gets(sstr);
  for (i = 0; i < nrec; i++) {
    if (strfind(sstr, data[i].name) || strfind(sstr, data[i].nname)) {
      clrscr();
      data[i].putdata();
      if (!getch()) {
        getch();
      }
    }
  }
}

void findbynumber() {
  char nstr[ALENGTH];
  cout << "\nEnter the Telephone Number to be Searched : ";
  gets(nstr);
  for (i = 0; i < nrec; i++) {
    if (strfind(nstr, data[i].telenumber)) {
      clrscr();
      data[i].putdata();
      if (!getch()) {
        getch();
      }
    }
  }
}

void findbyplace() {
  char pstr[ALENGTH];
  cout << "\nEnter a Part of the Address to be Searched : ";
  gets(pstr);
  for (i = 0; i < nrec; i++) {
    if (strfind(pstr, data[i].email) || strfind(pstr, data[i].add1) ||
        strfind(pstr, data[i].add2) || strfind(pstr, data[i].city) ||
        strfind(pstr, data[i].pincode) || strfind(pstr, data[i].state) ||
        strfind(pstr, data[i].country)) {
      clrscr();
      data[i].putdata();
      if (!getch()) {
        getch();
      }
    }
  }
}

void ffind() {
  char str[ALENGTH];
  cout << "\nEnter the String to be Searched : ";
  gets(str);
  for (i = 0; i < nrec; i++) {
    if (strfind(str, data[i].name) || strfind(str, data[i].nname) ||
        strfind(str, data[i].telenumber) || strfind(str, data[i].email) ||
        strfind(str, data[i].add1) || strfind(str, data[i].add2) ||
        strfind(str, data[i].city) || strfind(str, data[i].pincode) ||
        strfind(str, data[i].state) || strfind(str, data[i].country)) {
      clrscr();
      data[i].putdata(1);
      if (!getch()) {
        getch();
      }
    }
  }
}

void addrec() {
  tele temp;
  if (nrec >= MAX) {
    cout << "\nSorry Bub ,No Space Left !\n";
    if (!getch()) {
      getch();
    }
    return;
  }
  temp.getdata();
  for (i = 0; i < nrec; i++) {
    if (strcmp(temp.telenumber, data[i].telenumber) == 0) {
      break;
    }
  }
  if (i < nrec) {
    cout << "\nDuplicate Record Found (use Update) !\n";
    if (!getch()) {
      getch();
    }
    return;
  }
  data[nrec++] = temp;
  // cout<<"\nAdded !\n";
}

void updrec() {
  char temno[ALENGTH];
  if (nrec == 0) {
    cout << "\nThere ain't any Records at all !\n";
    if (!getch()) {
      getch();
    }
    return;
  }
  cout << "\nEnter Telephone Number : ";
  gets(temno);
  for (i = 0; i < nrec; i++) {
    if (strcmp(temno, data[i].telenumber) == 0) {
      break;
    }
  }
  if (i == nrec) {
    cout << "\nDude ,No Records Found !\n";
    if (!getch()) {
      getch();
    }
    return;
  }
  cout << "\nFound :\n";
  data[i].putdata(1);
  data[i].getdata();
  // cout<<"\nUpdated !\n";
}

void delrec() {
  char temno[ALENGTH];
  int pos;
  if (nrec == 0) {
    cout << "\nThere ain't any Records at all !\n";
    if (!getch()) {
      getch();
    }
    return;
  }
  cout << "\nEnter Telephone Number : ";
  gets(temno);
  for (i = 0; i < nrec; i++) {
    if (strcmp(temno, data[i].telenumber) == 0) {
      break;
    }
  }
  if (i == nrec) {
    cout << "\nDude ,No Records Found !\n";
    if (!getch()) {
      getch();
    }
    return;
  }
  // cout<<"\nFound :\n";data[i].putdata(1);
  pos = i;
  for (i = pos; i < nrec - 1; i++) {
    data[i] = data[i + 1];
  }
  nrec--;
  // cout<<"\nDeleted !\n";
}

void printall() {
  for (i = 0; i < nrec; i++) {
    data[i].putdata();
    if (!getch()) {
      getch();
    }
    clrscr();
  }
}

void main() {
  int choice;
  int pos;
  init();
  do {
    clrscr();
    cout << "\nMenu :";
    cout << "\n1 => Add Number";
    cout << "\n2 => Edit Number";
    cout << "\n3 => Delete Number";
    cout << "\n4 => Search By Name";
    cout << "\n5 => Search By Number";
    cout << "\n6 => Search By Address";
    cout << "\n7 => Search";
    cout << "\n8 => Print All Numbers";
    cout << "\n9 => Quit and Save";
    cout << "\nEnter Appropriate Number : ";
    cin >> choice;
    clrscr();
    if (choice == 1) {
      addrec();
    } else if (choice == 2) {
      updrec();
    } else if (choice == 3) {
      delrec();
    } else if (choice == 4) {
      findbyname();
    } else if (choice == 5) {
      findbynumber();
    } else if (choice == 6) {
      findbyplace();
    } else if (choice == 7) {
      ffind();
    } else if (choice == 8) {
      printall();
    }
    clrscr();
  } while (choice != 9);
  finish();
}