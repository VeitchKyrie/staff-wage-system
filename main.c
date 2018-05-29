//coding:utf-8
//author:黄业广
#include"stdio.h"//头文件
#include"stdlib.h"
#include"string.h"

typedef struct Basic_information
{
    char work_ID[80];
    char ID_number[80];
    char name[80];
    char gender[80];
    int age;
    int work_age;
    char department[80];
    char job[80];
    int job_ID;
    char home_number[80];
    char person_number[80];
}BI;//定义职工基本信息结构体

typedef struct Basic_wage_information
{
    int basic_wage;
    int job_wage;
    int else_wage;
    int reward;
    int wage_total;
}BW;//定义工资基础信息结构体

typedef struct Cost_information
{
    int home_cost;
    int job_insurance;
    int age_insurance;
    int person_tax;
}CI;//定义费用扣除结构体

typedef struct fee_information
{
    int water_fee;
    int electricity_fee;
    int clean_fee;
    int TV_fee;
}FI;//定义工资单数据结构体

typedef struct information
{
    BI basic;
    BW wage;
    CI cost;
    FI fee;
    struct information *prior;
    struct information *next;
}*info,infor;//定义总信息结构体

info creat_head()
{
    info head;
    head=(info)malloc(sizeof(infor));
    head->prior=NULL;
    head->next=NULL;
    return head;
}//初始化头结点

int user_choose()
{
    printf("||                This program has seven choose!                ||\n");
    printf("||                  Please make your choose!                    ||\n");
    printf("||       1--entry information      2--modify information        ||\n");
    printf("||       3--insert information     4--delete information        ||\n");
    printf("||       5--search information     6--count information         ||\n");
    printf("||                           0--END                             ||\n");
    printf("                          your choose:");
    int choose;
    scanf("%d",&choose);
    return choose;
}//用户选择界面

void sc(info p)
{
    printf("||               Now enter the basic information!               ||\n");
    printf("                     work ID:");
    scanf("%s",p->basic.work_ID);
    printf("                     ID number:");
    scanf("%s",p->basic.ID_number);
    printf("                     name:");
    scanf("%s",p->basic.name);
    printf("                     gender:");
    scanf("%s",p->basic.gender);
    printf("                     age:");
    scanf("%d",&p->basic.age);
    printf("                     work age:");
    scanf("%d",&p->basic.work_age);
    printf("                     department:");
    scanf("%s",p->basic.department);
    printf("                     job:");
    scanf("%s",p->basic.job);
    printf("                     job ID:");
    scanf("%d",&p->basic.job_ID);
    printf("                     home number:");
    scanf("%s",p->basic.home_number);
    printf("                     person number:");
    scanf("%s",p->basic.person_number);
    printf("||             Now enter your basic wage information!           ||\n");
    printf("                     basic wage:");
    scanf("%d",&p->wage.basic_wage);
    printf("                     job wage:");
    scanf("%d",&p->wage.job_wage);
    printf("                     else wage:");
    scanf("%d",&p->wage.else_wage);
    printf("                     reward:");
    scanf("%d",&p->wage.reward);
    printf("||               Now enter the cost information!                ||\n");
    printf("                     home cost:");
    scanf("%d",&p->cost.home_cost);
    printf("                     job insurance:");
    scanf("%d",&p->cost.job_insurance);
    printf("                     age insurance:");
    scanf("%d",&p->cost.age_insurance);
    p->wage.wage_total=p->wage.basic_wage+p->wage.else_wage+p->wage.job_wage+p->wage.reward;
    if(p->wage.wage_total<3500) p->cost.person_tax=0;
    else p->cost.person_tax=(p->wage.wage_total-3500)*0.1;
    printf("||               Now enter the fee information!                 ||\n");
    printf("                     water fee:");
    scanf("%d",&p->fee.water_fee);
    printf("                     electricity fee:");
    scanf("%d",&p->fee.electricity_fee);
    printf("                     clean fee:");
    scanf("%d",&p->fee.clean_fee);
    printf("                     TV fee:");
    scanf("%d",&p->fee.TV_fee);
}//用户界面输入

void pr(info p)
{
    printf("||                     Basic information:                       ||\n");
    printf("                       work ID:%s                                 \n",p->basic.work_ID);
    printf("                       ID number:%s                               \n",p->basic.ID_number);
    printf("                       name:%s                                    \n",p->basic.name);
    printf("                       gender:%s                                  \n",p->basic.gender);
    printf("                       age:%d                                     \n",p->basic.age);
    printf("                       work age:%d                                \n",p->basic.work_age);
    printf("                       department:%s                              \n",p->basic.department);
    printf("                       job:%s                                     \n",p->basic.job);
    printf("                       job ID:%d                                  \n",p->basic.job_ID);
    printf("                       home number:%s                             \n",p->basic.home_number);
    printf("                       person number:%s                           \n",p->basic.person_number);
    printf("||                  Basic wage information:                       \n");
    printf("                       basic wage:%d                              \n",p->wage.basic_wage);
    printf("                       job wage:%d                                \n",p->wage.job_wage);
    printf("                       else wage:%d                               \n",p->wage.else_wage);
    printf("                       reward:%d                                  \n",p->wage.reward);
    printf("||                    Cost information:                         ||\n");
    printf("                       home cost:%d                               \n",p->cost.home_cost);
    printf("                       job insurance:%d                           \n",p->cost.job_insurance);
    printf("                       age insurance:%d                           \n",p->cost.age_insurance);
    printf("                       person tax:%d                              \n",p->cost.person_tax);
    printf("||                    Fee information:                          ||\n");
    printf("                       water fee:%d                               \n",p->fee.water_fee);
    printf("                       electricity fee:%d                         \n",p->fee.electricity_fee);
    printf("                       clean fee:%d                               \n",p->fee.clean_fee);
    printf("                       TV fee:%d                                  \n",p->fee.TV_fee);
}//用户界面输出

void new_list(info head)
{
    info p,q;
    p=head;
    int a;
    do
    {
        q=(info)malloc(sizeof(infor));
        printf("||                     Please enter info!                       ||\n");
        sc(q);
        p->next=q;
        q->prior=p;
        p=q;
        p->next=NULL;
        printf("                        Continue? 1/0  ");
        scanf("%d",&a);
    }while(a==1);
}//建立新的数据链表

int read_file(info head)
{
    info p=head,q;
    FILE *fp;
    if((fp=fopen("initial_list.dat","rb"))==NULL) return 0;//如果读取文件为空,则没有创建过数据文件,返回0
    else
    {
        fp=fopen("initial_list.dat","rb");
        while(!feof(fp))
        {
            q=(info)malloc(sizeof(infor));
            fread(q,sizeof(infor),1,fp);
            p->next=q;
            q->prior=p;
            q->next=NULL;
            p=q;
        }
        p->prior->next=NULL;
        free(p);
        fclose(fp);
        return 1;//如果已经创建过数据文件,则读取到内存中,然后返回1
    }
}//读取文件中的数据

void save_file(info head)
{
    info p=head;
    FILE *fp;
    fp=fopen("initial_list.dat","wb+");
    while(p->next!=NULL)
    {
        p=p->next;
        fwrite(p,sizeof(infor),1,fp);
    }
    fclose(fp);
}//把内存中的数据保存到文件

info search_key(info head)
{
    info p=head;
    int choose;
    printf("The keyword:\n1--work_ID\n2--name\nYour choose:");
    scanf("%d",&choose);//选择以哪种关键字来查询
    if(choose==1)
    {
        char a[80];
        printf("work_ID:");
        scanf("%s",a);
        while(p->next!=NULL)
        {
            p=p->next;
            if(!strcmp(a,p->basic.work_ID)) return p;//如果查询成功,则返回指针
        }
        if(p->next==NULL) return NULL;//如果查询失败,返回空
    }
    else if(choose==2)
    {
        char b[80];
        printf("name:");
        scanf("%s",b);
        while(p->next!=NULL)
        {
            p=p->next;
            if(!strcmp(b,p->basic.name)) return p;//如果查询成功,则返回指针
        }
        if(p->next==NULL) return NULL;//如果查询失败,返回空
    }
}//用关键词语查询信息

void search_list(info head)
{
    info p=head,q;
    int choose;
    printf("||         You have two ways to search the information!         ||\n");
    printf("||  1--search all information!  2--search keyword information!  ||\n");
    printf("                       Your choose: ");
    scanf("%d",&choose);//选择那种方式查询
    if(choose==1)
    {
        printf("||                    The information:                          ||\n");
        int a=1;
        while(p->next!=NULL)
        {
            p=p->next;
            printf("                            (%d)                                  \n",a++);
            pr(p);
        }//循环链表把链表显示出来
    }
    else if(choose==2)
    {
        q=search_key(head);//接收关键词语查询信息返回的指针
        if(q!=NULL)
        {
        printf("||          The information you want to search:               ||\n");
            pr(q);//若指针不为空,显示指针指向的结构体信息
        }
        else if(q==NULL) printf("||          The keyword can't find!                         ||\n");//若指针为空,显示找不到
    }
}//查询信息

void modify_list(info head)
{
    info q=head,p;
    printf("which one you want to modify?\nYou can search the information you want to modify in keyword!\n");
    p=search_key(q);//用关键词语查询信息查询出要修改的信息
    printf("The information you want to modify:\n");
    pr(p);//显示出来查看修改哪一数据
    printf("Which one you want to modify?\n");
    printf("1--work ID\n2--ID number\n3--name\n4--gender\n5--age\n6--work age\n7--department\n8--job\n9--job ID\n10--home number\n11--person number\n12--basic wage\n13--job wage\n14--else wage\n15--reward\n16--home cost\n17--job insurance\n18--age insurance\n19--person tax\n20--water fee\n21--electricity fee\n22--clean fee\n23--TV fee\nYour choose: ");
    int a;
    scanf("%d",&a);
    printf("New date:");
    switch(a)
    {
        case 1 :scanf("%s",p->basic.work_ID);break;
        case 2 :scanf("%s",p->basic.ID_number);break;
        case 3 :scanf("%s",p->basic.name);break;
        case 4 :scanf("%s",p->basic.gender);break;
        case 5 :scanf("%d",&p->basic.age);break;
        case 6 :scanf("%d",&p->basic.work_age);break;
        case 7 :scanf("%s",p->basic.department);break;
        case 8 :scanf("%s",p->basic.job);break;
        case 9 :scanf("%d",&p->basic.job_ID);break;
        case 10:scanf("%s",p->basic.home_number);break;
        case 11:scanf("%s",p->basic.person_number);break;
        case 12:scanf("%d",&p->wage.basic_wage);break;
        case 13:scanf("%d",&p->wage.job_wage);break;
        case 14:scanf("%d",&p->wage.else_wage);break;
        case 15:scanf("%d",&p->wage.reward);break;
        case 16:scanf("%d",&p->cost.home_cost);break;
        case 17:scanf("%d",&p->cost.job_insurance);break;
        case 18:scanf("%d",&p->cost.age_insurance);break;
        case 19:scanf("%d",&p->cost.person_tax);break;
        case 20:scanf("%d",&p->fee.water_fee);break;
        case 21:scanf("%d",&p->fee.electricity_fee);break;
        case 22:scanf("%d",&p->fee.clean_fee);break;
        case 23:scanf("%d",&p->fee.TV_fee);break;
    }//修改数据
}//修改信息

void delete_list(info head)
{
    info p=head,q;
    printf("Search the information you want to delete in keyword!\n");
    q=search_key(p);//用关键词语查询信息查询出要删除的信息
    if(q==NULL) printf("The key can't find!\n");
    else if(q!=NULL)
    {
        printf("The information you want to delete:\n");
        pr(q);
        printf("yes? 1/0  ");//是否确定删除
        int a;
        scanf("%d",&a);
        if(a==1)
        {
            if(q->next!=NULL)
            {
                q->prior->next=q->next;
                q->next->prior=q->prior;
                free(q);
            }
            else
            {
                q->prior->next=q->next;
                q->prior=NULL;
                free(q);
            }
        }//删除数据
    }

}//删除信息

void insert_list(info head)
{
    info p=head,q,l;
    printf("Search the information your want to insert in keyword!\n");
    q=search_key(p);//用关键词语查询要添加的信息的节点位置
    if(q==NULL) printf("The key can't find!\n");
    else if(q!=NULL)
    {
        printf("The information you want to insert:\n");
        pr(q);
        printf("You want to insert in the next? 1/0  ");//询问要添加在节点前面还是后面
        int a;
        scanf("%d",&a);
        if(a==1)
        {
            if(q->next!=NULL)
            {
                l=(info)malloc(sizeof(infor));
                sc(l);
                l->next=q->next;
                l->prior=q;
                q->next->prior=l;
                q->next=l;
            }//非最后一个的添加
            else 
            {
                l=(info)malloc(sizeof(infor));
                sc(l);
                q->next=l;
                l->prior=q;
                l->next=NULL;
            }//最后一个的添加
        }//添加后面
        else if(a==0)
        {
            l=(info)malloc(sizeof(infor));
            sc(l);
            l->prior=q->prior;
            l->next=q;
            q->prior->next=l;
            q->prior=l;
        }//添加前面
    }
}//插入信息

int free_list(info head)
{
    info p=head;
    int choose;
    printf("||           You have entered the information already!          ||\n");
    printf("|| Do you enter new information by clearing the old information!||\n");
    printf("                       Your choose:(1/0)  ");
    scanf("%d",&choose);//询问是否销毁链表
    if(choose==1)
    {
        p->next->prior=NULL;
        p->next=NULL;
        printf("Your old information is cleared!\n");
        return 1;//销毁链表返回1
    }
    else if(choose==0) return 0;//不销毁链表返回0
}//销毁链表

void count_list(info head)
{
    info p=head;
    int choose;
    printf("You can count in following ways!\n1--age count\n2--wage count\n3--tax count\n4--wage sorting\nYour choose: ");
    scanf("%d",&choose);//选择哪种统计
    switch(choose)
    {
        case 1 :
            {
                int a=0,b=0,c=0;
                while(p->next!=NULL)
                {
                    p=p->next;
                    if((p->basic.age)<20) a++;
                    else if((p->basic.age)>=20&&(p->basic.age)<=55) b++;
                    else if((p->basic.age)>55) c++;
                }
                printf("The Young employees number:%d\nThe Middle-aged employees number:%d\nThe Retired employees number:%d\n",a,b,c);
                break;
            }//统计人数
        case 2 :
            {
                int basic_wage1=0,job_wage1=0,else_wage1=0,wage_total1=0;
                int basic_wage2=0,job_wage2=0,else_wage2=0,wage_total2=0;
                int basic_wage3=0,job_wage3=0,else_wage3=0,wage_total3=0;
                int d=0,e=0,f=0;
                while(p->next!=NULL)
                {
                    p=p->next;
                    if(!strcmp(p->basic.job,"human"))
                    {
                        basic_wage1=basic_wage1+p->wage.basic_wage;
                        job_wage1=job_wage1+p->wage.job_wage;
                        else_wage1=else_wage1+p->wage.else_wage;
                        wage_total1=wage_total1+basic_wage1+job_wage1+else_wage1;
                        d++;
                    }//统计工资同时统计人数
                    else if(!strcmp(p->basic.job,"finance"))
                    {
                        basic_wage2=basic_wage2+p->wage.basic_wage;
                        job_wage2=job_wage2+p->wage.job_wage;
                        else_wage2=else_wage2+p->wage.else_wage;
                        wage_total2=wage_total2+basic_wage2+job_wage2+else_wage2;
                        e++;
                    }//统计工资同时统计人数
                    else if(!strcmp(p->basic.job,"technology"))
                    {
                        basic_wage3=basic_wage3+p->wage.basic_wage;
                        job_wage3=job_wage3+p->wage.job_wage;
                        else_wage3=else_wage3+p->wage.else_wage;
                        wage_total3=wage_total3+basic_wage3+job_wage3+else_wage3;
                        f++;
                    }//统计工资同时统计人数
                }
                printf("human:\nnum:%d\nbasic wage total:%d\njob wage total:%d\nelse wage total:%d\nwage total:%d\nwage average:%d\n",d,basic_wage1,job_wage1,else_wage1,wage_total1,wage_total1/d);
                printf("finance:\nnum:%d\nbasic wage total:%d\njob wage total:%d\nelse wage total:%d\nwage total:%d\nwage average:%d\n",e,basic_wage2,job_wage2,else_wage2,wage_total2,wage_total2/e);
                printf("technology:\nnum:%d\nbasic wage total:%d\njob wage total:%d\nelse wage total:%d\nwage total:%d\nwage average:%d\n",f,basic_wage3,job_wage3,else_wage3,wage_total3,wage_total3/f);
                printf("The company total wage:%d\n",wage_total1+wage_total2+wage_total3);
                break;
            }//统计工资
        case 3 :
            {
                int total,tax,tax_total=0,tax_year;
                while(p->next!=NULL)
                {
                    p=p->next;
                    total=(p->wage.basic_wage)+(p->wage.else_wage)+(p->wage.job_wage)+(p->wage.reward);
                    if(total<3500) tax=0;
                    else tax=(total-3500)*0.1;
                    tax_total=tax_total+tax;
                }//统计一个月的税金
                tax_year=tax_total*12;//统计一年的税金
                printf("The company'tax one mouth:%d\nThe company'tax one year:%d\n",tax_total,tax_year);
                break;
            }//统计税金
        case 4 :
            {
                info head1=creat_head();
                info head_max=creat_head();
                info n=head_max;
                info l=head_max;
                info m=head1;
                info q,max;
                info t=head;
                int a=1;
                while(t->next!=NULL)
                {
                    t=t->next;
                    q=(info)malloc(sizeof(infor));
                    *q=*t;
                    m->next=q;
                    q->prior=m;
                    q->next=NULL;
                    m=q;
                }//复制一个链表
                while(head1->next!=NULL)
                {
                    max=head1->next;
                    q=head1->next;
                    while(q!=NULL)
                    {
                        if(((max->wage.basic_wage)+(max->wage.else_wage)+(max->wage.job_wage)+(max->wage.reward))<((q->wage.basic_wage)+(q->wage.else_wage)+(q->wage.job_wage)+(q->wage.reward)))
                            max=q;
                        q=q->next;
                    }
                    m=max;//找出链表中应发工资的最大值
                    if(max->next!=NULL)
                    {
                        max->prior->next=max->next;
                        max->next->prior=max->prior;
                    }
                    else
                    {
                        max->prior->next=max->next;
                        max->prior=NULL;
                    }
                    n->next=m;
                    m->prior=n;
                    m->next=NULL;
                    n=m;//将最大值的数据依次接入链表头节点
                }
                free(head1);
                while(l->next!=NULL)
                {
                    l=l->next;
                    printf("                            (%d)                                  \n",a++);
                    pr(l);
                }//把排序后的链表显示出来
                head_max->next->prior=NULL;
                head_max->next=NULL;//销毁排序后链表
                break;
            }//按应发工资排序
    }
}//统计

int main()
{
    info head;
    head=creat_head();//定义头结点
    printf("==================================================================\n");
    printf("||                           Hello!                             ||\n");
    printf("||             It's my honor to make this program!              ||\n");
    printf("||     This program is collecting the info of the works!        ||\n");
    printf("||                Please use it in English!                     ||\n");
    printf("||                        Thank you!                            ||\n");
    int choose,i=0;
    i=read_file(head);//检测是否存在文件,如果存在则读取进内存
    while(1)//循环让用户选择功能
    {
        choose=user_choose();
        switch(choose)
        { 
            case 1 :if(i==0) 
                    {
                        new_list(head);
                        save_file(head);
                        i=1;
                        break;
                    } //如果没有存在文件,则新建数据并保存
                    else if(i==1) //如果存在文件
                    {
                        int a;
                        a=free_list(head);//询问是否要销毁,然后重新创建
                        if(a==0) break;//不重新创建
                        else if(a==1)
                        {
                            new_list(head);
                            save_file(head);
                            break;
                        }//重新创建并保存到文件
                    }
            case 2 :if(i==0) 
                    {
                        printf("||             You haven't entered the information!             ||\n");
                        printf("||            Please enter the information firstly!             ||\n");
                        break;
                    }//如果没有存在文件,引导至新建数据
                    else
                    {
                        modify_list(head);
                        save_file(head);
                        break;
                    }//若存在,修改数据并保存文件
            case 3 :if(i==0) 
                    {
                        printf("||             You haven't entered the information!             ||\n");
                        printf("||            Please enter the information firstly!             ||\n");
                        break;
                    }//如果没有存在文件,引导至新建数据
                    else
                    {
                        insert_list(head);
                        save_file(head);
                        break;
                    }//若存在数据,则进行插入操作
            case 4 :if(i==0) 
                    {
                        printf("||             You haven't entered the information!             ||\n");
                        printf("||            Please enter the information firstly!             ||\n");
                        break;
                    }//如果没有存在文件,引导至新建数据
                    else
                    {
                        delete_list(head);
                        save_file(head);
                        break;
                    }//若存在数据,则进行删除操作
            case 5 :if(i==0) 
                    {
                        printf("||             You haven't entered the information!             ||\n");
                        printf("||            Please enter the information firstly!             ||\n");
                        break;
                    }//如果没有存在文件,引导至新建数据
                    else
                    {
                        search_list(head);
                        save_file(head);
                        break;
                    }//若存在数据,则进行查找操作
            case 6 :if(i==0) 
                    {
                        printf("||             You haven't entered the information!             ||\n");
                        printf("||            Please enter the information firstly!             ||\n");
                        break;
                    }//如果没有存在文件,引导至新建数据
                    else
                    {
                        count_list(head);
                        break;
                    }//若存在数据,则进行统计操作
            case 0 :exit(0);//退出程序
        }
    }
    return 0 ;
}