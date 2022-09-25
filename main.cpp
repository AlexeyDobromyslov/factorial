#include <iostream>
#include <cmath>

using namespace std;
struct TElement{//������� ������������ ������
    int info;//�������� ��������
    TElement*Right;//��������� �� ������ �������
    TElement*Left;//��������� �� ����� �������
};
    TElement*create(){
    TElement*Element= new TElement;
    Element->Left=NULL;
    Element->Right=NULL;
    return Element;
    }
    TElement*create(int info){
    TElement*Element= new TElement;
    Element->Left=NULL;
    Element->Right=NULL;
    Element->info=info;
    return Element;
    }
  TElement* addLeft(TElement* start_list){//������� ���������� �������� ����� �� ������
	TElement*Element= new TElement;
	Element->Right=start_list;//����� ������ �������� ��������� �� ������ ������
	start_list->Left=Element;//���� ������ ������ ��������� �� ����� �������
	Element->Left=NULL;

	return Element;
    }
    TElement* addRight(TElement* finish_list){//������� ���������� �������� ������ �� ������
    TElement*Element= new TElement;
	Element->Right=NULL;
	Element->Left=finish_list;//���� ������ �������� ��������� �� ����� ������
	finish_list->Right=Element;//����� ����� ������ ��������� �� ����� �������

	return Element;
    }
    void list_del(TElement* first_digit){//�������� ������ ����� � �����
    TElement *right,*left;
    right=first_digit;//��������� �������
    while(right){//���� ��������� ���� �� ���-������
    left=right->Left;//������� � ����������� ��������
    delete right;//������� �������
    right=left;//���������� ���� �������
    }
    }
     int catch_digit(int num, int num_digit){
         if(num_digit>0){
         int exponent=pow(10,num_digit-1);
         return (num%(int)pow(10,num_digit))/exponent;
         }
         return -1;
    }
    string tostring9(int number){
        int digit;
        int exponent;
        string result;
        string string_digit;
            //���������� ������� �����
        for(int i=1; i<10;i++){
        digit=catch_digit(number, i);
        string_digit=to_string(digit);
        result.insert(0,string_digit);
        }

    return result;
    }

class TNumber{//�����
public:
    TNumber(){
    first_digit=NULL;
    amount=0;
    last_digit=NULL;
    };
    TNumber(TElement* one){
    first_digit=one;
    last_digit=one;
    amount=1;
    }


    TElement* first_digit;//��������� �� ������ ������
    TElement* last_digit;//��������� �� ��������� ������
    int amount;//���-�� �������� � �����
    TNumber operator++(int){
        int transfer_flag=0, exit_flag=0;//���� �������� ������ �������
        if(first_digit){
        TElement* temp=first_digit;
        int i=0;

        while(temp&&exit_flag==0){
        if(i==0){//���� ��� ������ ��������
         temp->info++;//��������� �������� �������
        }else{
        temp->info+=transfer_flag;//����� ������� ������� � ������ ��� ��������� ���������� �������
        if(temp->info<=999999999){//��������� ����� � ������ ���� ���� �������� ��� �� ��������
            exit_flag=1;
        }
        transfer_flag=0;
        }
        //������������ �������
        if(temp->info>999999999){
            temp->info-=1000000000;
            transfer_flag=1;
        }
          i++;
          temp=temp->Left;
        }
         if(transfer_flag==1){//� ������ ������������� ������ ������� ������� ��� ���� ������
            last_digit=addLeft(last_digit);
            last_digit->info=1;
            amount++;
         }
        }
    }


    TNumber operator+=(TNumber num2){
        if(first_digit&&num2.first_digit){
            if(amount<num2.amount){
                TElement* last=last_digit;
                while(amount<num2.amount){
                    last=addLeft(last);
                    last->info=0;
                    amount++;
                }
                last_digit=last;


            }

            TElement* temp1=first_digit, *temp2=num2.first_digit;
            int transfer_flag=0;
            int exit_flag=0;
            while(exit_flag==0){
            if(temp2){
            temp1->info+=temp2->info;
            }
            temp1->info+=transfer_flag;
            if(transfer_flag!=0){
            transfer_flag=0;}
            if(temp1->info>999999999){
            temp1->info-=1000000000;
            transfer_flag=1;
            }
            if(!temp2){//���� ������� ������������� ���������
            temp1=temp1->Left;
                if(!(temp1&&transfer_flag==1)){//�������,����� �� ��������� ����������� ������,
                   //���� �� ����. ������������ ������, ���� ��� ����
                    exit_flag=1;
                }
            }else{
            temp2=temp2->Left;
            temp1=temp1->Left;
            if(!temp1){
                exit_flag=1;
            }
            }
            }

            if(transfer_flag==1){//� ������ ������������� ������ ������� ������� ��� ���� ������
            last_digit=addLeft(last_digit);
            last_digit->info=1;
            amount++;

         }

        }
         //return *this;

    }
    TNumber operator*=(TNumber num2){
        if(first_digit&&num2.first_digit){

                TNumber storage=TNumber(create(0));
                TElement* temp1, *temp2=num2.first_digit;
                int digit1, digit2, result, add, transfer, place_transfer, global1=0,global2=0, i, j, search_unit, flag_search;

                while(temp2){//���������� �� ������� �����, �� ������� ��������
                        temp1=first_digit;
                        global1=0;
                  while(temp1){//�������� �� ������� ����������� �����
                    j=0;

                    while(j<9){//�������� �� �������� ������ ����������� �����
                        //�����, ���������� � ���������� ��������� ������� ����� �� ������ �������
                        TNumber add_storage=TNumber(create(0));
                        TElement *add_temp;
                        i=0;
                       transfer=0;//����� ������� ������ �� ��������
                       while(i<9){//�������� �� �������� ������ ����������� �����
                           add_temp=add_storage.first_digit;
                           digit1=catch_digit(temp1->info,i+1);//������� ������ ������� �����
                           digit2=catch_digit(temp2->info,j+1);//������� ������ ������� �����

                           result=digit1*digit2;//��������� ��������� ���� ��������
                           result+=transfer;//��������� ���� ������������ ������
                           add=result-result/10*10; //����� ������� ������ ����������
                           transfer=result/10; //����� ������� ������ ����������
                           //���� ������� ��������������� �����������
                           add*=(int)pow(10, (i+j)%9);
                           //cout<<add<<endl;
                           place_transfer=(i+j+1)%9;


                           search_unit=0;//������, � ������� �������� ������
                           flag_search=0;
                           TElement*point=NULL;

                           while(add_temp&&flag_search==0){//���� ���������� ������ ��� �������
                                if(search_unit==global1+global2+(i+j)/9){
                                    flag_search=1;
                                    add_temp->info+=add;//���� ���������� ������, ������� � �� ������
                                }else{//����� ��� �� ������ ������
                                point=add_temp;//���������� ��������� ������������
                                add_temp=add_temp->Left;
                                if(add_temp){//���� ��������� ������ ����������
                                search_unit++;
                                }

                                }
                           }

                           //� ������, ���� ���������� ������ ���, �������

                           if(flag_search==0){
                                add_temp=point;//��������� �� ��������� ������������ ������
                            while(flag_search==0){//!!!!!!!!!!!!!!!!!!!!!!!!!
                                add_temp=addLeft(add_temp);//������� �����
                                add_temp->info=0;
                                search_unit++;
                                add_storage.last_digit=add_temp;//��������� ��������� �� ��������� �������
                                add_storage.amount++;//����������� ���-�� ���������
                                if(search_unit==global1+global2+(i+j)/9){//������ �� ��� ������?
                                    flag_search=1;
                                    add_temp->info+=add;//���� ������, �������� ������ � �� � ������ �� �����

                                }

                            }
                           }

                           if(temp1->info%(int)pow(10,i+1)==temp1->info){//�������� ��������� �������� �������� (��� ������� "000000789")
                            break;
                           }
                           i++;

                        }
                          if(transfer!=0){//���� ������� ������ �������� ����� ��������� ������� ����� �� ������ �������

                                if(place_transfer==0){//���� ��� ������ ������, �� ��� ������, ��� ����� ���������, ����� ������
                                add_temp=addLeft(add_temp);
                                add_temp->info=0;
                                add_storage.last_digit=add_temp;
                                add_storage.amount++;
                                add_temp->info=transfer;
                                }else{
                                add_temp->info+=transfer*(int)pow(10, place_transfer);
                                }
                            }
                        storage+=add_storage;//��������� ��������� � ����� ��������
                        add_storage.del();//������� ����� ���������
                    if(temp2->info%(int)pow(10,j+1)==temp2->info){//�������� ��������� �������� �������� (��� ������� "000000056")
                            break;
                           }
                     j++;


                    }
                    global1++;
                    temp1=temp1->Left;
                  }
                   global2++;
                 temp2=temp2->Left;

                }
                list_del(first_digit);
                first_digit=storage.first_digit;
                last_digit=storage.last_digit;
                amount=storage.amount;



        }
    }
    //���� ����� � �������
    int input(){
    string number;
    cout<<"\n positive number=";
    cin>>number;

    int amount_element=number.size()/9;
    int num=-999999;

    int first_iter=0;
    int pos=number.find_first_not_of("0123456789");//�������� �� �����
    if(pos!=string::npos){
     cout<<"inputed value not positive number"<< endl;
     first_digit=last_digit=NULL;
     amount=0;
     return 0;
    }
    if(number.size()%9!=0){//���� ����� ����� �������� 6
            //������������ ������ �������, ������� �� ������ � ������� � �����
            num=stoi(number.substr(0,number.size()%9));
            if(num!=0){
            first_digit=create(num);
            last_digit=first_digit;
            amount++;
            first_iter=1;
            }
    }
    for(int i=0; i<amount_element; i++){
            //������������ ������� ��������, ������� � ��� ������������������, ���� ����� ����
            num=stoi(number.substr(i*9+number.size()%9,9));
            if(first_iter==0){//���� ��� ������ �������� ���������� � ������
            if(num!=0){
            first_digit=create(num);
            last_digit=first_digit;
            amount++;
            first_iter=1;
            }
            }else{
            first_digit=addRight(first_digit);
            first_digit->info=num;
            amount++;
            }

     }

    return 0;
    }
    int convert(int number){

        int digit, digit_send;
        //���-���� ���� ���� �������� ��������� �� ����� ���� �� ��� ������� ������������
            first_digit=create(0);
            last_digit=first_digit;
            amount++;
            //���������� ������� ����� (�� ����� ������� ����� ���������� ��� ���� � 4 �����)
        for(int i=1; i<=10;i++){
        digit=catch_digit(number, i);//������� ������ �����
        digit_send=digit*pow(10,i-1);
         if(i==10){//���� ������� � ��������� ��������� ������
            if(digit!=0){//���� ������ �� ����� ����
            last_digit=addLeft(last_digit);
            amount++;
            last_digit->info=digit;
            }
        }else{
        last_digit->info+=digit_send;
        }
        }

    return 0;
    }
    /*TElement* addLeft(){//������� ���������� �������� ����� �� ������
	TElement*Element= new TElement;
	Element->Right=first_digit;//����� ������ �������� ��������� �� ������ ������
	first_digit->Left=Element;//���� ������ ������ ��������� �� ����� �������
	Element->Left=NULL;
	first_digit=Element;
	return Element;
    }
    TElement* addRight(){//������� ���������� �������� ������ �� ������
    TElement*Element= new TElement;
	Element->Right=NULL;
	Element->Left=first_digit;//���� ������ �������� ��������� �� ����� ������
	first_digit->Right=Element;//����� ����� ������ ��������� �� ����� �������
	first_digit=Element;
	return Element;
    }*/
    //�������� ������ ����� � �����
    void del(){
    TElement *right,*left;
    right=first_digit;//��������� �������
    while(right){//���� ��������� ���� �� ���-������

    left=right->Left;//������� � ����������� ��������
    delete right;//������� �������
    right=left;//���������� ���� �������
    }
    amount=0;
    first_digit=last_digit=NULL;
    }
    //����� �����
    void show(){
    TElement *right,*left;
    left=last_digit;//��������� �������
    //���� � ������� ��������
    if(left){
        cout<<"your number is ";
    }
    int i=0;
    while(left){

    if(i==0){//���� ��� ��������� ������
     cout<<left->info<<"|";
    }else{
        cout<<tostring9(left->info)<<"|";//������� ������� ��� 9 (����� �� 1|1|, � 1|000000001)

    }
    left=left->Right;//������� � ����������  ��������
    i++;
    }
    cout<<endl;
    }
};
TNumber factorial(int fact){
    TNumber num=TNumber(create(1)), num2=TNumber(create(1));

    if(fact<=1){
        num2.del();
        return num;
    }
    for(int i=2; i<=fact; i++){
        num2++;
        num*=num2;
    }
    num2.del();
    return num;
}

int main()
{
     TNumber num=factorial(1000);
    num.show();
    num.del();




    return 0;
}
