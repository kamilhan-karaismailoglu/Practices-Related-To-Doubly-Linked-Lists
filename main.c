#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    struct node * next;
    struct node * prev;
};

char sayi1[50]="";
char sayi2[50]="";
int uzunluk = 0;
int geciciListe[10];

struct node * liste1 = NULL;
struct node * liste2 = NULL;

int main()
{
    txtDosyasindanOku();

    ParcalaVeDonustur(sayi1);
    for(int i=0; i<uzunluk/3;i++)
    {
        EkleListe1(geciciListe[i]);
    }

    ParcalaVeDonustur(sayi2);
    for(int i=0; i<uzunluk/3;i++)
    {
        EkleListe2(geciciListe[i]);
    }

    //Listele();

    ListeleriKarsilastir();
    //printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    //Listele();

    printf("\n Sayi 1 :");
    Birlestir(liste1);
    printf("\n Sayi 2 :");
    Birlestir(liste2);
    return 0;
}

void txtDosyasindanOku()
{
    FILE * fPtr;

    if( (fPtr = fopen("Sayilar.txt","r"))==NULL)
    {
        printf("dosya olusturulamadi..");
        return -1;
    }
    else
    {
        fseek(fPtr,0,SEEK_SET);
        char rakam="";
        int sayac = 0;
        int yeniSayiMi = 0;

        do{
            fscanf(fPtr,"%c",&rakam);

            if(rakam=='#')
            {
                yeniSayiMi=1;
                uzunluk = sayac;
                sayac=0;
                continue;
            }
            else
            {
                if(yeniSayiMi==0)
                {
                    sayi1[sayac] = rakam;
                    sayac++;
                }
                else
                {
                    sayi2[sayac] = rakam;
                    sayac++;
                }
            }

        }while(!feof(fPtr));
        sayi2[sayac-1]=NULL;

        fclose(fPtr);
    }
}

void ParcalaVeDonustur(char sayi[50])
{
    int sayac = 0;
    int ElemanSayisi = strlen(sayi)/3;

    for(int i= 1; i<=ElemanSayisi;i++)
    {
        int baslangicIndisi = 3*(i-1);
        int deger[3];

        for(int j=0; j<3;j++)
        {
            deger[j]=sayi[baslangicIndisi]-'0';
            baslangicIndisi++;
        }
        int intDeger = deger[0]*100+deger[1]*10+deger[2];
        geciciListe[sayac]=intDeger;
        sayac++;
    }
}

void EkleListe1(int key)
{
    if(liste1==NULL)
    {
        liste1 = (struct node *)malloc(sizeof(struct node));
        liste1->data=key;
        liste1->next=NULL;
        liste1->prev=NULL;
    }
    else
    {
        struct node* temp = liste1;
        struct node* temp2 = (struct node *)malloc(sizeof(struct node));
        temp2->data=key;

        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=temp2;
        temp2->next=NULL;
        temp2->prev=temp;
    }
}

void EkleListe2(int key)
{
    if(liste2==NULL)
    {
        liste2 = (struct node *)malloc(sizeof(struct node));
        liste2->data=key;
        liste2->next=NULL;
        liste2->prev=NULL;
    }
    else
    {
        struct node* temp = liste2;
        struct node* temp2 = (struct node *)malloc(sizeof(struct node));
        temp2->data=key;

        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=temp2;
        temp2->next=NULL;
        temp2->prev=temp;
    }
}

void Listele()
{
    struct node * temp = liste1;
    while(temp!=NULL)
    {
        printf("deger = %d - adres= %d - next= %d - prev= %d\n",temp->data,temp,temp->next,temp->prev);
        temp=temp->next;
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++\n");

    struct node * temp2 = liste2;
    while(temp2!=NULL)
    {
        printf("deger = %d - adres= %d - next= %d - prev= %d\n",temp2->data,temp2,temp2->next,temp2->prev);
        temp2=temp2->next;
    }
}

void ListeleriKarsilastir()
{
    struct node * temp = liste1;
    struct node * temp2 = liste2;
    int indis=0;

    while(temp!=NULL)
    {
        indis++;

        if(temp->data > temp2->data)
        {
            struct node * current = liste1;
            struct node * prev=NULL, * next =NULL;

            while(current!=NULL)
            {
                next = current->next;
                current->next = prev;
                current->prev = next;

                prev = current;
                current= next;
            }
            liste1= prev;
        }

        else if (temp->data == temp2->data)
        {
            struct node * current = liste2;
            struct node * prev=NULL,*next =NULL;

            while(current!=NULL)
            {
                next = current->next;
                current->next = prev;
                current->prev = next;

                prev = current;
                current= next;
            }
            liste2= prev;
        }

        else
        {
            int geciciPrev = temp->prev;
            int geciciNext = temp->next;

            temp->next= temp2->next;
            temp2->next= geciciNext;

            temp->prev = temp2->prev;
            temp2->prev = geciciPrev;

            if(temp->prev!=NULL)
            {
                temp = temp->prev;
                temp2 = temp2->prev;

                int geciciNext = temp->next;
                temp->next= temp2->next;
                temp2->next= geciciNext;

                geciciNext = temp->next;
                temp = temp2->next;
                temp2 = geciciNext;
            }

            if(temp->next!=NULL)
            {
                temp = temp->next;
                temp2 = temp2->next;

                int geciciPrev = temp->prev;
                temp->prev = temp2->prev;
                temp2->prev = geciciPrev;

                geciciPrev = temp->prev;
                temp = temp2->prev;
                temp2= geciciPrev;
            }
        }

        temp= liste1;
        temp2= liste2;

        for(int i=0; i<indis;i++)
        {
            temp=temp->next;
            temp2=temp2->next;
        }
    }
}

void Birlestir(struct node* temp)
{
    sayi1[50]=NULL;
    int sayac =0;
    while(temp!=NULL)
    {
        int sayi = temp->data;
        int yuzlerB = sayi/100;
        sayi -= yuzlerB*100;
        int onlarB = sayi/10;
        sayi-= onlarB*10;

        char c1 = yuzlerB+'0';
        char c2 = onlarB+'0';
        char c3 = sayi+'0';

        sayi1[sayac]=c1;
        sayac++;
        sayi1[sayac]=c2;
        sayac++;
        sayi1[sayac]=c3;
        sayac++;

        temp=temp->next;
    }

    for(int i=0; i<uzunluk;i++)
    {
        printf("%c",sayi1[i]);
    }
}









