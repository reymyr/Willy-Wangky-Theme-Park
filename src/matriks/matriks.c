#include "matriks.h"
#include "../boolean.h"
#include <stdio.h>

MATRIKS CMatriks;
boolean ENDMATRIKS;

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    NBrsEff(*M)=NB;
    NKolEff(*M)=NK;
}


/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxMatriksValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    return (i>=BrsMin && i<=BrsMax && j>=KolMin && j<=KolMin);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    return NBrsEff(M) + GetFirstIdxBrs(M) - 1;
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    return NKolEff(M) + GetFirstIdxKol(M) - 1;
}
boolean IsIdxMatriksEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    return (i>=GetFirstIdxBrs(M) && i<= GetLastIdxBrs(M) && j>=GetFirstIdxKol(M) && j<=GetLastIdxKol(M));
}

/* ********** KELOMPOK BACA/TULIS ********** */ 

void TulisMATRIKS(MATRIKS M, FILE *f){
    // Menyalin isi Matriks M ke dalam file bernama <filename>
    for (int i = 0; i <= GetLastIdxBrs(M); i++){
        for (int j = 0; j < GetLastIdxKol(M); j++)
        {
            fprintf(f,"%c",Elmt(M,i,j));
        }
        if (i!=GetLastIdxBrs(M)){
            fprintf(f,"%c\n",Elmt(M,i,GetLastIdxKol(M))); 
        } else
        {
            fprintf(f,"%c",Elmt(M,i,GetLastIdxKol(M)));
        }        
    }
}

void PrintMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (di akhir tiap baris, tidak ada spasi)
* * *
* _ *
* * *
*/
{
    indeks i,j;
    for (i=GetFirstIdxBrs(M);i<GetLastIdxBrs(M);i++)
    {
        for (j=GetFirstIdxKol(M);j<GetLastIdxKol(M);j++)
        {
            printf("%c ",Elmt(M,i,j));
        }
        //j = last id kolom 
        printf("%c",Elmt(M,i,GetLastIdxKol(M)));
        printf("\n");
    }
    // i==id terakhir baris matriks
    for (j=GetFirstIdxKol(M);j<GetLastIdxKol(M);j++)
    {
        printf("%c ",Elmt(M,GetLastIdxBrs(M),j));
    }
    printf("%c\n",Elmt(M,GetLastIdxBrs(M),GetLastIdxKol(M)));
}


/* ******** KELOMPOK PEMROSESAN BEBERAPA MATRIKS YANG DIBACA DARI SEBUAH FILE ********* */

void STARTMATRIKS(char *filename){
    MK_START(filename);

    if (MK_CC == MK_MARK)
    {
        ENDMATRIKS = true;
    } else
    {
        ENDMATRIKS = false;
        SalinMatriks();
    }
}

void ADVMATRIKS(){
/* I.S. : CC dapat berupa MARK atau SEPARATOR 
   F.S. : CMatriks adalah matriks terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, ENDMATRIKS = true.     
   Proses : Akuisisi matriks menggunakan procedure SalinMatriks */
   if (MK_CC==MK_MARK)
   {
       ENDMATRIKS = true;
   } else //CC==SEPARATOR
   {
       MK_ADV(); // CC = ENTER
       MK_ADV(); // CC sudah di elemen karakter pertama matriks yang akan diakusisi
       SalinMatriks();
   }
}

void SalinMatriks(){
/* Mengakuisisi matriks, menyimpan dalam CMatriks
   I.S. : CC adalah karakter pertama dari matriks
   F.S. : CMatriks berisi matriks yang sudah diakuisisi{} 
          CC = SEPARATOR atau CC = MARK
          CC adalah karakter sesudah karakter terakhir yang diakuisisi. */
    char ENTER = '\n';
    int NB=0;
    int NK=0;

    while (MK_CC!=SEPARATOR && MK_CC!=MK_MARK)
    {
        if (MK_CC==ENTER)
        {
            NB++;
            NK=0;
        } else
        {
            Elmt(CMatriks,NB,NK) = MK_CC;
            NK++;
        }
        MK_ADV();
    }
    NBrsEff(CMatriks) = NB+1;
    NKolEff(CMatriks) = NK+1;
}

/* ********** Operasi lain ********** */
int NBElmtMatriks (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
    return NBrsEff(M)*NKolEff(M);
}