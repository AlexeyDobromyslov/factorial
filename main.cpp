#include <iostream>
#include <cmath>

using namespace std;
struct TElement{//элемент двухсвязного списка
    int info;//значения элемента
    TElement*Right;//указатель на правый элемент
    TElement*Left;//указатель на левый элемент
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
  TElement* addLeft(TElement* start_list){//функция добавления элемента слева от списка
	TElement*Element= new TElement;
	Element->Right=start_list;//право нового элемента указывает на начало списка
	start_list->Left=Element;//лево начала списка указывает на новый элемент
	Element->Left=NULL;

	return Element;
    }
    TElement* addRight(TElement* finish_list){//функция добавления элемента справа от списка
    TElement*Element= new TElement;
	Element->Right=NULL;
	Element->Left=finish_list;//лево нового элемента указывает на конец списка
	finish_list->Right=Element;//право конца списка указывает на новый элемент

	return Element;
    }
    void list_del(TElement* first_digit){//удаление списка числа с конца
    TElement *right,*left;
    right=first_digit;//последний элемент
    while(right){//пока указывает хоть на что-нибудь
    left=right->Left;//перешли к предыдущему элементу
    delete right;//удалили текущий
    right=left;//предыдущий стал текущим
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
            //поразрядно передам число
        for(int i=1; i<10;i++){
        digit=catch_digit(number, i);
        string_digit=to_string(digit);
        result.insert(0,string_digit);
        }

    return result;
    }

class TNumber{//число
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


    TElement* first_digit;//указатель на первый разряд
    TElement* last_digit;//указатель на последний разряд
    int amount;//кол-во разрядов в числе
    TNumber operator++(int){
        int transfer_flag=0, exit_flag=0;//флаг создания нового разряда
        if(first_digit){
        TElement* temp=first_digit;
        int i=0;

        while(temp&&exit_flag==0){
        if(i==0){//если это первая итерация
         temp->info++;//инкремент младшего разряда
        }else{
        temp->info+=transfer_flag;//иначе перенос разряда в случае его появления немладшему разряду
        if(temp->info<=999999999){//досрочный выход в случае если флаг переноса уже не появится
            exit_flag=1;
        }
        transfer_flag=0;
        }
        //нормалтзация разряда
        if(temp->info>999999999){
            temp->info-=1000000000;
            transfer_flag=1;
        }
          i++;
          temp=temp->Left;
        }
         if(transfer_flag==1){//в случае существования нового разряда создать под него ячкйку
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
            if(!temp2){//если разряды прибавляемого кончились
            temp1=temp1->Left;
                if(!(temp1&&transfer_flag==1)){//смотрим,можно ли прибавить переносимый разряд,
                   //если он есть. существующей ячейке, если она есть
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

            if(transfer_flag==1){//в случае существования нового разряда создать под него ячкйку
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

                while(temp2){//проходимся по ячейкам числа, на которое умножаем
                        temp1=first_digit;
                        global1=0;
                  while(temp1){//проходим по ячейкам умножаемого числа
                    j=0;

                    while(j<9){//проходим по разрядам ячейки умножающего числа
                        //число, получаемое в результате умножения первого числа на разряд второго
                        TNumber add_storage=TNumber(create(0));
                        TElement *add_temp;
                        i=0;
                       transfer=0;//самый старший разряд из переноса
                       while(i<9){//проходим по разрядам ячейки умножаемого числа
                           add_temp=add_storage.first_digit;
                           digit1=catch_digit(temp1->info,i+1);//цепляем разряд первого числа
                           digit2=catch_digit(temp2->info,j+1);//цепляем разряд второго числа

                           result=digit1*digit2;//результат умножения двух разрядов
                           result+=transfer;//результат плюс перенесенный разряд
                           add=result-result/10*10; //взяли младший разряд результата
                           transfer=result/10; //взяли старший разряд результата
                           //даем разряду соответствующую разрядность
                           add*=(int)pow(10, (i+j)%9);
                           //cout<<add<<endl;
                           place_transfer=(i+j+1)%9;


                           search_unit=0;//ячейка, в которую поместим разряд
                           flag_search=0;
                           TElement*point=NULL;

                           while(add_temp&&flag_search==0){//ищем подходяшую ячейку для разряда
                                if(search_unit==global1+global2+(i+j)/9){
                                    flag_search=1;
                                    add_temp->info+=add;//если подходящая ячейка, заносим в неё разряд
                                }else{//иначе идём по списку дальше
                                point=add_temp;//запоминаем последнюю существующую
                                add_temp=add_temp->Left;
                                if(add_temp){//если следующая ячейка существует
                                search_unit++;
                                }

                                }
                           }

                           //в случае, если подходящей ячейки нет, создаем

                           if(flag_search==0){
                                add_temp=point;//переходим на последнюю существующую ячейку
                            while(flag_search==0){//!!!!!!!!!!!!!!!!!!!!!!!!!
                                add_temp=addLeft(add_temp);//создаем новую
                                add_temp->info=0;
                                search_unit++;
                                add_storage.last_digit=add_temp;//обновляем указатель на последний элемент
                                add_storage.amount++;//увеличиваем кол-во элементов
                                if(search_unit==global1+global2+(i+j)/9){//нужная ли это ячейка?
                                    flag_search=1;
                                    add_temp->info+=add;//если нужная, помещаем разряд в неё и уходим из цикла

                                }

                            }
                           }

                           if(temp1->info%(int)pow(10,i+1)==temp1->info){//проверка отсутсвия значимых разрядов (для случаев "000000789")
                            break;
                           }
                           i++;

                        }
                          if(transfer!=0){//если остался разряд переноса после умножения первого числа на разряд второго

                                if(place_transfer==0){//если его разряд первый, то это значит, что нужно создавать, новую ячейку
                                add_temp=addLeft(add_temp);
                                add_temp->info=0;
                                add_storage.last_digit=add_temp;
                                add_storage.amount++;
                                add_temp->info=transfer;
                                }else{
                                add_temp->info+=transfer*(int)pow(10, place_transfer);
                                }
                            }
                        storage+=add_storage;//результат добавляем в общее значение
                        add_storage.del();//удаляем общий результат
                    if(temp2->info%(int)pow(10,j+1)==temp2->info){//проверка отсутсвия значимых разрядов (для случаев "000000056")
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
    //ввод числа в консоль
    int input(){
    string number;
    cout<<"\n positive number=";
    cin>>number;

    int amount_element=number.size()/9;
    int num=-999999;

    int first_iter=0;
    int pos=number.find_first_not_of("0123456789");//проверка на число
    if(pos!=string::npos){
     cout<<"inputed value not positive number"<< endl;
     first_digit=last_digit=NULL;
     amount=0;
     return 0;
    }
    if(number.size()%9!=0){//если длина числа некратна 6
            //конвертируем первые символы, которые не входят в шестёрки с конца
            num=stoi(number.substr(0,number.size()%9));
            if(num!=0){
            first_digit=create(num);
            last_digit=first_digit;
            amount++;
            first_iter=1;
            }
    }
    for(int i=0; i<amount_element; i++){
            //конвертируем шестёрки символов, начиная с уже отконвертированных, если такие есть
            num=stoi(number.substr(i*9+number.size()%9,9));
            if(first_iter==0){//если это первая итерация добавления в список
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
        //все-таки надо было заменить структуру на класс хотя бы для наличия конструктора
            first_digit=create(0);
            last_digit=first_digit;
            amount++;
            //поразрядно передам число (но можно сделать двумя итерациями для инта в 4 байта)
        for(int i=1; i<=10;i++){
        digit=catch_digit(number, i);//цепляем разряд числа
        digit_send=digit*pow(10,i-1);
         if(i==10){//если перещли к следующей разрядной ячейке
            if(digit!=0){//если разряд не равен нулю
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
    /*TElement* addLeft(){//функция добавления элемента слева от списка
	TElement*Element= new TElement;
	Element->Right=first_digit;//право нового элемента указывает на начало списка
	first_digit->Left=Element;//лево начала списка указывает на новый элемент
	Element->Left=NULL;
	first_digit=Element;
	return Element;
    }
    TElement* addRight(){//функция добавления элемента справа от списка
    TElement*Element= new TElement;
	Element->Right=NULL;
	Element->Left=first_digit;//лево нового элемента указывает на конец списка
	first_digit->Right=Element;//право конца списка указывает на новый элемент
	first_digit=Element;
	return Element;
    }*/
    //удаление списка числа с конца
    void del(){
    TElement *right,*left;
    right=first_digit;//последний элемент
    while(right){//пока указывает хоть на что-нибудь

    left=right->Left;//перешли к предыдущему элементу
    delete right;//удалили текущий
    right=left;//предыдущий стал текущим
    }
    amount=0;
    first_digit=last_digit=NULL;
    }
    //вывод числа
    void show(){
    TElement *right,*left;
    left=last_digit;//последний элемент
    //идем к первому элементу
    if(left){
        cout<<"your number is ";
    }
    int i=0;
    while(left){

    if(i==0){//если это последний разряд
     cout<<left->info<<"|";
    }else{
        cout<<tostring9(left->info)<<"|";//выводим элемент под 9 (чтобы не 1|1|, а 1|000000001)

    }
    left=left->Right;//перешли к следующему  элементу
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
