#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX1 10000

void delay(float sekunde){  
    int mili_sekunde = sekunde * 1000;
	clock_t trenutnoV = clock();
    while (clock() < trenutnoV + mili_sekunde);
};

void random(FILE *fptr, int n){
	int i,a;
	srand(time(NULL));
	for(i=0;i<n;i++){
		a=rand()%254+1;
		fprintf(fptr,"%d\n",a);
	}
}

int provera(char *unos){
	
	if(strcmp(unos,"1")==0 || strcmp(unos,"2")==0 || strcmp(unos,"0")==0){
		return 1;
	}
	else{
		printf("Pogresan unos!\n");
		delay(0.8);
		printf("Mozete koristiti samo ponudjene brojeve -> 1, 2 ili 0\n");
		delay(0.8);
		return 0;
	}
	
};

int provera2(char *unos){
	
	if(strcmp(unos,"1")==0 || strcmp(unos,"2")==0 || strcmp(unos,"3")==0){
		return 1;
	}
	else{
		printf("Pogresan unos!\n");
		delay(0.8);
		printf("Mozete koristiti samo ponudjene opcije -> 1, 2 ili 3\n");
		delay(0.8);
		return 0;
	}
	
};

void povratak_u_meni(){
	delay(2);
	printf("\nTekst je uspesno sifriran.");
	delay(1);
	printf("\nSigurnosno brisanje originala u toku...");
	delay(3);
	remove("original.txt");
	printf("\nOriginal uspesno obrisan!");
	delay(0.5);
	printf("\nPovratak u meni programa u toku...\n");
	delay(2);
};

void ispis_kodiranog_teksta(FILE *fptr){
	char c;
	fseek(fptr,0,SEEK_SET);
	printf("\n*************************************************************************************\n");
	while((c=fgetc(fptr))!=EOF)
		putchar(c);
	printf("\n*************************************************************************************\n");
}

void kod_vise_tri(FILE *fptr1, FILE *fptr2){
	char c;
	printf("\nTekst se trenutno sifruje, molimo vas sacekajte...\n");
	delay(3);
	while((c=fgetc(fptr1))!=EOF){
		c=c+3;
		fputc(c,fptr2);
	}
	fseek(fptr2,0,SEEK_SET);
	ispis_kodiranog_teksta(fptr2);
}

void kod_rotacija_bitova(FILE *fptr1, FILE *fptr2){
	char c;
	int c1, pom1, pom2;
	printf("\nTekst se trenutno sifruje, molimo vas sacekajte...\n");
	delay(3);
	while((c=fgetc(fptr1))!=EOF){
		c1=c;
		pom1=1;
		pom2=1;
		pom2<<=1;
		pom1=pom1&c1;
		pom2=pom2&c1;
		pom1<<=6;
		pom2<<=6;
		c1>>=2;
		c1=c1|pom1;
		c1=c1|pom2;
		c=c1;
		fputc(c1,fptr2);
	}
	rewind(fptr2);
	ispis_kodiranog_teksta(fptr2);
	fclose(fptr2);
};

void kod_random_vrednosti(FILE *original, FILE *sifrant, FILE *sifra){
	int r,i;
	char c,c1;
	srand(17);
	r=rand()%254+1;
	printf("\nTekst se trenutno sifruje, molimo vas sacekajte...\n");
	delay(3);
	while((c=fgetc(original))!=EOF){
		fscanf(sifra,"%d",&i);
		c1=i;
		c=c+((c1+r)/2);
		fputc(c,sifrant);
	}
	rewind(sifrant);
	ispis_kodiranog_teksta(sifrant);
	fclose(original);
	fclose(sifrant);
	fclose(sifra);
}

int potvrda(){
	char c;
	printf("\nDekodiranje je gotovo. Ukoliko ste zadovoljni pritisnite bilo koji taster.\nU slucaju da zelite isti tekst da dekodirate drugom metodom, unesite karakter '0': ");
	fflush(stdin);
	c=getchar();
	if(c!='\n'){
		delay(1);
		printf("\nIzvinjavamo se na gresci. Ubrzo cete biti vraceni na ponovni izbor kljuca za dekodiranje...\n");
		delay(2);
		return 0;
	}
	else{
		delay(1);
		printf("\nU redu, uskoro cete biti vraceni u glavni meni...\n");
		delay(2);
		return 1;
	}
};

void dekod_manje_tri(FILE *fptr){
	char c;
	fseek(fptr,0,SEEK_SET);
	printf("*************************************************************************************\n");
	while((c=fgetc(fptr))!=EOF){
		c=c-3;
		delay(0.1);
		putchar(c);
	}
	printf("\n*************************************************************************************\n");
};

void dekod_rotacija_bitova(FILE *fptr){
	char c;
	unsigned c1,pom1,pom2;
	fseek(fptr,0,SEEK_SET);
	printf("*************************************************************************************\n");
	while((c=fgetc(fptr))!=EOF){
		c1=c;
		pom1=1;
		pom2=1;
		pom1<<=6;
		pom2<<=7;
		pom1=c1&pom1;
		pom2=c1&pom2;
		pom1>>=6;
		pom2>>=6;
		c1<<=2;
		c1=c1|pom1;
		c1=c1|pom2;
		c=c1;
		delay(0.1);
		printf("%c",c);

	}
	printf("\n*************************************************************************************\n");
};

void dekod_random_vrednosti(FILE *sifrant, FILE *sifra){
	int r,i;
	char c,c1;
	srand(17);
	r=rand()%254+1;
	printf("*************************************************************************************\n");
	while((c=fgetc(sifrant))!=EOF){
		fscanf(sifra,"%d",&i);
		c1=i;
		c=c-((c1+r)/2);
		delay(0.1);
		putchar(c);
	}
	printf("\n*************************************************************************************\n");
}

