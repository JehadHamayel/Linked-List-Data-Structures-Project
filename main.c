//Jehad Hamayel
//1200348
//sec: 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define destChar 30
#define numOfCharInLine 200
////functions prototype
typedef struct Passengers* passengersPtr;//Define a new variable type name
struct Passengers{//Define a new type of passenger data
    int travelerID;
    int travellingDate;
    char from[destChar];
    char to[destChar];
    passengersPtr next;//An indication of where a data will be stored in memory
    char travellingTime[5];
};
typedef passengersPtr PassPtr;//Define a new variable type name
typedef struct Busses* bussesPtr;//Define a new variable type name
struct Busses{////Define a new type of Busses data
    int busNum ;
    int date;
    char from[destChar];
    char to[destChar];
    int priceOfTicket;
    int capacity;
    int size;
    char departureTime[5];

    PassPtr p ;//Mark another type of pointer, from another type of data, to create a linked list of linked list
    bussesPtr next;//An indication of where a data will be stored in memory

};
bussesPtr Blast;//Definition of a global variable of type Bussers
PassPtr Plast;//Definition of a global variable of type Passengers
////functions prototype
void readBFile (bussesPtr);//A function to read from a buses-type data file
void readPFile (PassPtr);//Function to read from a Passengers data file
void insertBuss(bussesPtr ,bussesPtr );//Add a bus to the linked list
void insertPass(PassPtr ,PassPtr );//Add a passenger on the linked list
void assignPassAndPrintBuss(bussesPtr,PassPtr,PassPtr);//Reservation of passengers in buses
void printASpecificBus(bussesPtr,int);//Printing information about a particular bus with the information of its passengers
void printUnmatchedPass(PassPtr );//Printing the information of unreserved passengers
void addNewPass(bussesPtr,PassPtr);//Adding a new passenger and reserving a place for him, if possible
int existsBefor(bussesPtr ,PassPtr ,int);//Checking the presence or absence of a passenger
void deletePass(bussesPtr,PassPtr);//Delete the reservation of a specific passenger on a specific bus
PassPtr FindPreviousPass(int,PassPtr );//Find the passenger before the passenger you want in Linked list
int IsLastPass (PassPtr ,PassPtr );//Check if the last passenger or not
int IsLastBuss (bussesPtr ,bussesPtr );//Check if the last bus or not
void deleteBus (bussesPtr,PassPtr);//Delete bus information and transport passengers on the non-reserved list
bussesPtr FindPreviousBuss(int  ,bussesPtr );//Find the buss before the buss you want in Linked list
int isInteger(char word[]);
int isPassFileEpty = 0;
int main()
{
    printf("-------------------------------------<<<<<<Welcome to my project>>>>>>-------------------------------------\n\n");
    int exit =0,readedB=0,readedP=0,assignded=0;//Defining variables of type integer
    char opch[10];
    //Reserving linked-list in memory and making the header point to NULL
    bussesPtr linkedbusses = (bussesPtr)malloc(sizeof(struct Busses));
    linkedbusses->next=NULL;
    PassPtr linkedPass = (PassPtr)malloc(sizeof(struct Passengers));
    linkedPass->next = NULL;
    PassPtr unmatchedPass = (PassPtr)malloc(sizeof(struct Passengers));
    unmatchedPass->next=NULL;
    while(!exit){//Create a loop that displays options for operations and call functions.
    printf("Enter the number of the option that you want:\n\n");
    printf("1. Load the bus information file\n");
    printf("2. Load the passenger information file\n");
    printf("3. Assign passengers and print assignment information of all busses\n");
    printf("4. Print a specific bus information along with its passengers information (names and IDs)\n");
    printf("5. Print unmatched passengers\n");
    printf("6. Add new passenger\n");
    printf("7. Delete passenger\n");
    printf("8. Delete bus number\n");
    printf("9. Exit\n\n");
    printf("Choose an option:");
    scanf("%s",opch);
    if(isInteger(opch)){//Check if the entry is a number
        int op=atoi(opch);
    printf("\n-------------------------------------------------------------\n\n");
    switch(op){
    case 1: if(!readedB){//Check if it is read or not
                readBFile (linkedbusses);//call read Busses function.
                printf("-------------------------------------------------------------\n\n");
                readedB=1;//File has been read
            }
            else{
                printf("The file has already been read\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 2:if(!readedP){//Check if it is read or not
                readPFile(linkedPass);//call read Passenger function.
                if(isPassFileEpty==1)
                    assignded=1;
                 printf("-------------------------------------------------------------\n\n");
                readedP=1;////File has been read
             }
             else{
                printf("The file has already been read\n\n");
                printf("-------------------------------------------------------------\n\n");
                }

    break;
    case 3:if(readedP&&readedB){//Check if it is read or not
                assignPassAndPrintBuss(linkedbusses,linkedPass,unmatchedPass);//Calling Function Reservation
                assignded=1;
            }else if(!readedP&&readedB){//Check if it is read or not
                printf("Please Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else if(!readedB&&readedP){//Check if it is read or not
                printf("Please Load the bus information file\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else{
                printf("Please Load the bus information file and Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 4:if(readedP&&readedB){//Check if it is read or not
           if(assignded) {//Confirmation of the reservation process
            printf("Please Enter the bus number that you want to print:");
            char busNumch[10]; scanf("%s",busNumch);
            while(!isInteger(busNumch)){//Check if the entry is a number
                    printf("Please choose a number\n");
                    scanf("%s",busNumch);
                    }
            int busNum=atoi(busNumch);
            printASpecificBus(linkedbusses,busNum);//Calling the specific bus printing function

            }else{
                printf("Please do assign passenger information first\n\n");
                printf("-------------------------------------------------------------\n\n");
            }
            }else if(!readedP&&readedB){//Check if it is read or not
                printf("Please Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else if(!readedB&&readedP){//Check if it is read or not
                printf("Please Load the bus information file\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else{
                printf("Please Load the bus information file and Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 5:if(readedP&&readedB){//Check if it is read or not
            if(assignded) {//Confirmation of the reservation process
             printUnmatchedPass(unmatchedPass);//Calling Function Print Unreserved List
            }else{
                printf("Please do assign passenger information first\n\n");
                printf("-------------------------------------------------------------\n\n");
            }

             }else if(!readedP&&readedB){//Check if it is read or not
                printf("Please Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else if(!readedB&&readedP){//Check if it is read or not
                printf("Please Load the bus information file\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else{
                printf("Please Load the bus information file and Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 6:
            if(readedP&&readedB){//Check if it is read or not
            if(assignded) {//Confirmation of the reservation process
                addNewPass(linkedbusses,unmatchedPass);//Calling function add a passenger
            }else{
                printf("Please do assign passenger information first\n\n");
                printf("-------------------------------------------------------------\n\n");
            }

            }else if(!readedP&&readedB){//Check if it is read or not
                printf("Please Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else if(!readedB&&readedP){//Check if it is read or not
                printf("Please Load the bus information file\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else{
                printf("Please Load the bus information file and Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 7:if(readedP&&readedB){//Check if it is read or not
        if(assignded) {//Confirmation of the reservation process
                 deletePass(linkedbusses,unmatchedPass);//Calling function delete passenger
            }else{
                printf("Please do assign passenger information first\n\n");
                printf("-------------------------------------------------------------\n\n");
            }

            }else if(!readedP&&readedB){
                printf("Please Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else if(!readedB&&readedP){
                printf("Please Load the bus information file\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else{
                printf("Please Load the bus information file and Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 8:if(readedP&&readedB){//Check if it is readed or not
        if(assignded) {//Confirmation of the reservation process
               deleteBus (linkedbusses,unmatchedPass);//Calling function delete bus
            }else{
                printf("Please do assign passenger information first\n\n");
                printf("-------------------------------------------------------------\n\n");
            }

            }else if(!readedP&&readedB){//Check if it is readed or not
                printf("Please Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else if(!readedB&&readedP){//Check if it is readed or not
                printf("Please Load the bus information file\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
            else{
                printf("Please Load the bus information file and Load the passenger information file first\n\n");
                printf("-------------------------------------------------------------\n\n");
                }
    break;
    case 9: exit=1 ;
            printf("-------------------------------------<<<<<<Thank You, Goodbey>>>>>>-------------------------------------\n\n");
    break;
    default : printf("Choose a correct number\n\n");
            printf("-------------------------------------------------------------\n\n");
    }
    }else{
        printf("\nPlease Choose a correct number\n\n");
            printf("-------------------------------------------------------------\n\n");}

    }
    return 0;
}

void readBFile (bussesPtr buslinked){//function definition.
    FILE *in;//Define file
    char inf[numOfCharInLine],*token;
    in = fopen("busses.txt","r");//Make the file in read
    if(in!=NULL){//Check if the file exists
    int isEmpty=1;
    while(fgets(inf,numOfCharInLine,in)!=NULL){//while loop for reading from file
    bussesPtr btemp = (bussesPtr)malloc(sizeof(struct Busses));//Create a node to group it with the bus linked list
    btemp->next=NULL;//Make the next node point to Null
    token = strtok(inf,"#");//String up to #
    btemp->busNum=atoi(token);//Converting a String to an Intger

    token = strtok(NULL,"#");//String up to #
    btemp->date=atoi(token);//Converting a String to an Intger

    token = strtok(NULL,"#");//String up to #
    strcpy(btemp->departureTime,token);//Copy the string and place it in the required variable

    token = strtok(NULL,"#");//String up to #
    strcpy(btemp->from,token);//Copy the string and place it in the required variable

    token = strtok(NULL,"#");//String up to #
    strcpy(btemp->to,token);//Copy the string and place it in the required variable

    token = strtok(NULL,"#");//String up to #
    btemp->priceOfTicket = atoi(token);//Converting a String to an Intger

    token = strtok(NULL,"#");//String up to #
    btemp->capacity=atoi(token);//Converting a String to an Intger
    btemp->size=0;//make size zero
    insertBuss(buslinked,btemp);//The function of adding the bus to the linked list
    isEmpty=0;
    }
    if(!isEmpty){//Check if the file is empty or not, then print the information we read
    bussesPtr t = buslinked->next;//Make the variable t point to the header
    printf("The data that was in the file:\n\n");
    printf("Bus Number  Date        Departure Time  From        To          Price of Ticket  Capacity\n");
    while(t!=NULL){//Start printing and transfer the pointer from one Node to another
        printf("%-10d  %-10d  %-14s  %-10s  %-10s  %-3d              %-3d\n",t->busNum,t->date,t->departureTime,t->from,t->to, t->priceOfTicket,t->capacity);
        t=t->next;
    }}
    else{
            printf("The File is empty Please put information inside it and then use the program\n");
            exit(1);
        }


    printf("\n-------------------------------------------------------------\n\n");
    fclose(in);//close file
    printf("The file has been read successfully\n\n");
    }
    else
        printf("File not found\n\n");
}
void insertBuss(bussesPtr buslinked,bussesPtr btemp){//function definition.
    btemp->p = (PassPtr)malloc(sizeof(struct Passengers));//Create a node header of passenger to group it with the bus linked list
    btemp->p->next=NULL;//Make the next node point to Null
    if(buslinked!=NULL&&btemp!=NULL){
    if(buslinked->next==NULL)//function adds the node to the Linkedlist
        Blast=buslinked;
    Blast->next=btemp;
    btemp->next=NULL;
    Blast=btemp;//Pointer point to the last node -> O(1)
    }
    else
        printf("No data has been reserved in order to add it to Linkedlist");

}
void readPFile(PassPtr p){//function definition.
    FILE *in;//Define file
    char inf[numOfCharInLine],*token;
    in = fopen("passengers.txt","r");//Make the file in read
    int isEmpty=1;
    if(in!=NULL){//Check if the file exists
    while(fgets(inf,numOfCharInLine,in)!=NULL){//while loop for reading from file
    PassPtr Ptemp = (PassPtr)malloc(sizeof(struct Passengers));//Create a node to group it with the passenger linked list
    Ptemp->next=NULL;//Make the next node point to Null
    token = strtok(inf,"#");//String up to #
    Ptemp->travelerID = atoi(token);//Converting a String to an Intger

    token = strtok(NULL,"#");//String up to #
    Ptemp->travellingDate = atoi(token);//Converting a String to an Intger

    token = strtok(NULL,"#");//String up to #
    strcpy(Ptemp->travellingTime,token);//Converting a String to an Intger

    token = strtok(NULL,"#");//String up to #
    strcpy(Ptemp->from,token);//Converting a String to an Intger

    token = strtok(NULL,"#\n");//String up to #
    strcpy(Ptemp->to,token);//Converting a String to an Intger
    insertPass(p,Ptemp);//The function of adding the passenger to the linked list
    isEmpty=0;
}
    if(!isEmpty){//Check if the file is empty or not, then print the information we read
        printf("The data that was in the file:\n\n");
        PassPtr t = p->next;//Make the variable t point to the header
        printf("Traveler ID  Travelling Date  Travelling Time  From        To        \n");
        while(t!=NULL){//Start printing and transfer the pointer from one Node to another
            printf("%-11d  %-15d  %-15s  %-10s  %-10s\n",t->travelerID,t->travellingDate,t->travellingTime,t->from,t->to);
            t=t->next;
    }
    } else{
            printf("The File is empty\n\n");
            isPassFileEpty=1;
        }
        if(isPassFileEpty ==0){
            printf("\n-------------------------------------------------------------\n\n");
            printf("The file has been read successfully\n\n");
    }
    fclose(in);//close file
    }
    else
        printf("File not found");
}
void insertPass(PassPtr p,PassPtr ptemp){//function definition.

    if(p!=NULL&&ptemp!=NULL){
        if(p->next==NULL)//function adds the node to the Linkedlist
            Plast =p;
        Plast->next=ptemp;
        ptemp->next = NULL;
        Plast = ptemp;//Pointer point to the last node -> O(1)
    }
    else
        printf("No data has been reserved in order to add it to Linkedlist");
}
void assignPassAndPrintBuss(bussesPtr buslinked,PassPtr passlinked,PassPtr unmatchPass){//function definition.
    //The function of the method is to book passengers on buses according to the passenger's information
    int isInsert = 0;
    PassPtr tpass = passlinked->next,temp;
    while(tpass!=NULL){//Loop pass on buses linked list
            bussesPtr tbuss = buslinked->next;
        while(tbuss!=NULL){//Loop pass on passenger linked list
               PassPtr tptr = tbuss->p;
                if((tbuss->date)==(tpass->travellingDate)&&(strcmp((tbuss->departureTime),(tpass->travellingTime))==0)&&(tbuss->size)<(tbuss->capacity)&&(strcmp((tbuss->from),(tpass->from))==0) &&(strcmp((tbuss->to),(tpass->to))==0))
                   {//Check that the passenger information matches the bus, then add it to the reservation
                    while(tptr->next!=NULL)
                            tptr=tptr->next;
                    temp = tpass;
                    passlinked->next=tpass->next;

                    tptr->next=temp;
                    temp->next=NULL;

                    tbuss-> size++;
                    isInsert=1;
                    break;
                }
    tbuss = tbuss->next;
    }
        if(!isInsert){//If the information does not match, the passenger must be added to the unmatch list
             PassPtr tptrM = unmatchPass;
             while(tptrM->next !=NULL)
               tptrM=tptrM->next;
             temp = tpass;
             passlinked->next=tpass->next;
             tptrM->next=temp;
             temp->next=NULL;
        }
        tpass =  passlinked->next;
        isInsert=0;
    }
    printf("The Information of all busses:\n\n");//Printing information of buses and passengers booked on them
    bussesPtr tbPr = buslinked->next;
    while(tbPr!=NULL){////Loop pass on buses linked list
        PassPtr tpPr=tbPr->p->next;
        printf("Bus Number: %d , Date: %d , Time: %s , From: %-10s , To: %-10s , Price of Ticket: %d , capacity: %d\n\n",tbPr->busNum,tbPr->date,tbPr->departureTime,tbPr->from,tbPr->to, tbPr->priceOfTicket,tbPr->capacity);
        if(tbPr->p->next!=NULL)
            printf("Passengers in the Bus %d:\n\n",tbPr->busNum);
        else
            printf("There are no passengers\n\n");
         int counter =1;
         while(tpPr!=NULL){//Loop pass on passenger linked list
            printf("%d- Passenger Id: %d , Date: %d , Time: %s , From: %-10s , To: %-10s\n",counter,tpPr->travelerID,tpPr->travellingDate,tpPr->travellingTime,tpPr->from,tpPr->to);
           counter++;
            tpPr=tpPr->next;
         }counter=1;
          printf("\n----------------------------------------------------------------------------------------------------------------------\n\n");
         tbPr = tbPr->next;
    }


}
void printASpecificBus(bussesPtr buslinked,int busNum){//function definition.
    //Function prints the information of a particular bus and the passengers in it
      bussesPtr tbuss = buslinked->next;
      int foundBuss =0;
        while(tbuss!=NULL){//Check if the bus is exists
            if(tbuss->busNum==busNum){
                foundBuss =1;
               break;
            }
            tbuss = tbuss->next;
        }
        if(foundBuss){//if it exists print information
            printf("\nBus Number: %d , Date: %d , Time: %s , From: %-10s , To: %-10s , Price of Ticket: %d , capacity: %d\n\n",tbuss->busNum,tbuss->date,tbuss->departureTime,tbuss->from,tbuss->to, tbuss->priceOfTicket,tbuss->capacity);
                  PassPtr tpPr=tbuss->p->next;
                  int counter =1;
                  if(tpPr==NULL)//Check if there are passengers
                    printf("There are no passengers\n\n");
                  while(tpPr!=NULL){//Print passenger information
                    printf("%d-Passenger Id: %d , Date: %d , Time: %s , From: %-10s , To: %-10s\n",counter,tpPr->travelerID,tpPr->travellingDate,tpPr->travellingTime,tpPr->from,tpPr->to);
                    counter++;
                    tpPr=tpPr->next;
                  }counter=1;
        }else
            printf("\nNot Founded Buss\n\n");
        printf("\n--------------------------------------------------------------------------------------------------------------------\n\n");

}
void printUnmatchedPass(PassPtr unmatchPass){//function definition.
    //Method is printing the unmatch list
 PassPtr tptrM = unmatchPass->next;
     printf("This is unmatched passengers:\n\n");
     if(tptrM==NULL)//Check if there are passengers
        printf("There are no passengers\n\n");
             while(tptrM !=NULL){
            printf("Passenger Id: %d , Date: %d , Time: %s , From: %-10s , To: %-10s\n",tptrM->travelerID,tptrM->travellingDate,tptrM->travellingTime,tptrM->from,tptrM->to);
               tptrM=tptrM->next;}
            printf("\n-------------------------------------------------------------------------------------\n\n");

}
void addNewPass(bussesPtr buslinked,PassPtr unmatchPass){//function definition.
    //Method's job is to add a passenger and reserve a place for him on the buses
    PassPtr tempPass = (PassPtr)malloc(sizeof(struct Passengers));//Create a node header of passenger to group it with the bus linked list
    tempPass->next=NULL;//Make the next node point to Null
    int isInsert=0;
    //The user is asked to enter the passenger information
    char word[10];
    printf("Enter the Id of Passenger\n");
    scanf("%s",word);
    while(!isInteger(word)){//Check if the entry is a number
          printf("Please choose a number\n");
         scanf("%s",word);
         }
    tempPass->travelerID = atoi(word);
    if(!existsBefor(buslinked,unmatchPass,tempPass->travelerID)){//Check if the user exists or not
     printf("Enter the Travelling Date of Passenger(e.g. (11042022)->(day(11),munth(04),year(2022))\n");
    scanf("%s",word);
    while(!isInteger(word)){//Check if the entry is a number
        printf("Please choose a number\n");
         scanf("%s",word);
         }
    tempPass->travellingDate = atoi(word);
    printf("Enter the Travelling Time of Passenger(HH:MM) (HH=00-23)(MM=00-59)\n");
    scanf("%s",tempPass->travellingTime);
    printf("Enter the from which destination of Passenger\n");
    scanf("%s",tempPass->from);
    printf("Enter the to which destination of Passenger\n");
    scanf("%s",tempPass->to);

     bussesPtr tbuss = buslinked->next;
        while(tbuss!=NULL){//Loop pass on buses linked list
               PassPtr tptr = tbuss->p;
                if((tbuss->date)==(tempPass->travellingDate)&&(strcmp((tbuss->departureTime),(tempPass->travellingTime))==0)&&(tbuss->size)<(tbuss->capacity)&&(strcmp((tbuss->from),(tempPass->from))==0) &&(strcmp((tbuss->to),(tempPass->to))==0))
                   {//Passenger information matching check
                    while(tptr->next!=NULL)
                            tptr=tptr->next;
                    tptr->next=tempPass;
                    tempPass->next=NULL;

                    tbuss-> size++;
                    isInsert=1;
                    printf("\nThe passenger has been added and a place has been reserved for him according to the information entered\n\n");
                    break;
                }
    tbuss = tbuss->next;
    }
        if(!isInsert){//If it does not match the information with any bus it is placed in the unmatch list
             PassPtr tptrM = unmatchPass;
             while(tptrM->next !=NULL)
               tptrM=tptrM->next;
             tptrM->next=tempPass;
             tempPass->next=NULL;
            printf("\nThe passenger was added, but no place was found for him to reserve a seat for him, either because his information did not match with a particular bus, or there is no place for him to reserve a seat for him\n\n");

        }
    }
    else
        printf("\nPassenger already exists, cannot be added \n\n");
}
int existsBefor(bussesPtr buslinked,PassPtr unmatchPass,int id){//function definition.
    //method you check if the passenger is found or not
    int existsPass = 0;
    bussesPtr tbuss = buslinked->next;
    while(tbuss!=NULL){//Loop pass on buses linked list to check
            if(FindPreviousPass(id ,tbuss->p)!=NULL)//If it has a previous element, then it exists
                existsPass=1;
        tbuss = tbuss->next;
}
    if(FindPreviousPass(id ,unmatchPass)!=NULL)//Check for the presence of the passenger in the unmatch list
        existsPass=1;
return existsPass;
}

void deletePass(bussesPtr buslinked,PassPtr unmatchPass){//function definition.
    //Method deletes a specific passenger on a bus
    int idPass,idBuss;
    //Ask the user to enter the bus number, the ID of the passenger
    char word[10];
    printf("Please Enter Id Of Buss that you want to Delete From: ");
    scanf("%s",word);
    while(!isInteger(word)){//Check if the entry is a number
         printf("Please choose a number\n");
         scanf("%s",word);
         }
    idBuss = atoi(word);

    printf("Please Enter Id Of Passenger that you want to Delete: ");
    scanf("%s",word);
    while(!isInteger(word)){//Check if the entry is a number
          printf("Please choose a number\n");
         scanf("%s",word);
         }
    idPass = atoi(word);

    int foundBuss=0;
     bussesPtr tbuss = buslinked->next;
     while(tbuss!=NULL){//Loop pass on buses linked list
            if(tbuss->busNum == idBuss){
               PassPtr tptr = tbuss->p;
                    PassPtr p,temp;
                    p = FindPreviousPass(idPass,tptr);
                    if(p==NULL){//Check if the passenger is in the bus or not
                        if(!existsBefor(buslinked,unmatchPass,idPass))//Check if it is on buses or not
                                printf("\nPassenger not found\n");
                        else
                             printf("\nIs it on another Bus\n\n");
                        foundBuss=1;
                        break;
                    }
                    else if(!IsLastPass(p,tptr)){//If it exists, it deletes the passenger
                        temp = p->next;
                        p->next = temp->next;
                        free(temp);
                        printf("The reservation has been canceled and the passenger has been deleted\n\n");
                        tbuss-> size--;
                        foundBuss=1;
                        break;
                    }
                }
    tbuss = tbuss->next;
    }
    if(!foundBuss){//If he is not on the bus, he searches the un match list to check the place only

                PassPtr tptr = unmatchPass;
                    PassPtr p;
                    p = FindPreviousPass(idPass,tptr);
                    if(p==NULL){//Check if the passenger is in the un match list or not
                        if(!existsBefor(buslinked,unmatchPass,idPass))
                                printf("\nPassenger not found\n");
                        else
                             printf("\nIs it on another Bus\n");
                        }
                    else if(!IsLastPass(p,tptr)){
                         printf("\nPassenger found in unmatched list\n\n");
                    }
            printf("\nBuss Not Founded\n\n");
    }
}
PassPtr FindPreviousPass(int X ,PassPtr L){//function definition.
    //Find the previous passenger to be searched for
    PassPtr p=L->next,s=L;
    while(p!= NULL && p->travelerID !=X){
        p = p->next;
        s=s->next;
        }
        if(p==NULL)
            return p;
        else
            return s;

}
int IsLastPass (PassPtr P,PassPtr L){//function definition.
    return P->next == NULL;
}
int IsLastBuss (bussesPtr P,bussesPtr L){//function definition.
    return P->next == NULL;
}
void deleteBus (bussesPtr buslinked,PassPtr unmatchPass){//function definition.
    //Method deletes bus and passenger transport information on the Unmatch list
    int idBuss;
    //Ask the user to enter the bus number
     char word[10];
     printf("Please Enter Id Of Buss that you want to Delete : ");
    scanf("%s",word);
    while(!isInteger(word)){//Check if the entry is a number
         printf("Please choose a number\n");
         scanf("%s",word);
         }
    idBuss = atoi(word);
    bussesPtr tbuss = buslinked;
    bussesPtr b,temp;
    b = FindPreviousBuss(idBuss,tbuss);
    if(b==NULL)
         printf("\nBus is not available\n\n");
   else if(!IsLastBuss(b,tbuss)){//Checks if the bus exists or not and then deletes it
    temp = b->next;
    b->next = temp->next;
    PassPtr tptrM = unmatchPass;
    while(tptrM->next !=NULL)
            tptrM=tptrM->next;
    tptrM->next=temp->p->next;
    temp->p->next->next=NULL;
    free(temp);
    printf("\nBus info deleted successfully\n");
    }

}
bussesPtr FindPreviousBuss(int X ,bussesPtr L){//function definition.
    //Find the previous Buss to be searched for
    bussesPtr b=L->next,s=L;
    while(b!= NULL && b->busNum !=X){
        b = b->next;
        s=s->next;
        }
        if(b==NULL)
            return b;
        else
            return s;
}
int isInteger(char word[]){
    int index ;
    for(index=0;index<strlen(word);index++){
        if(!isdigit(word[index]))
            return 0;
    }
    return 1;
}
