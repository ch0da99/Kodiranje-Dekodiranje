#include "zaglavlje.h"

main(){
	
	int br=0;
	char c, unos[2], *tekst;
	FILE *original, *sifra, *sifrant;
	
	system("mode 85,30");


	//uvodni tekst

	printf("------------------------------------> Welcome <--------------------------------------\n");
	delay(1);
	printf("---------> Seminarski rad iz predmeta PRJ: Kodiranje i Dekodiranje teksta <----------\n");
	delay(1);
	printf("----------------------------> Danijel Jovic - IS 17/17 <-----------------------------\n");
	delay(1);
	printf("Program se pokrece...\n");
	delay(3);

	do{

		//provera unosa opcije
		do{
			printf("\nUnesite broj u zavisnosti koju opciju zelite:\n1 -> Kodiranje\n2 -> Dekodiranje\n0 -> Izlaz iz programa\nVasa opcija je: ");
			fflush(stdin);
			gets(unos);
		}while(provera(unos)==0);

		switch(unos[0]){

		//Opcija kodiranja

		case '1': 
			tekst=(char *)malloc(MAX1+1);
			if(tekst==NULL){
				printf("\nNeuspela alokacija memorije za niz karaktera\n");
				exit(1);
			}
			original=fopen("original.txt", "w+");
			printf("\nIzabrali ste opciju kodiranja, za pocetak, unesite tekst koji zelite da bude kodiran \n(Prekid unosa mozete postici tako sto cete poslati red: \"()\").\nTekst: \n");
			
			//Unosenje teksta u datoteku

			do{
				gets(tekst);
				if(strcmp(tekst,"()")!=0){
					fwrite(tekst,sizeof(char),strlen(tekst),original);
					fputc('\n',original);
				}
			}while(strcmp(tekst,"()")!=0);
			free(tekst);
			fclose(original);
			printf("\nUspesno unesen tekst.\n");
			delay(1);

			//izbor nacina sifrovanja

			do{
				printf("\nSada izaberite kojom metodom zelite da sifrujemo uneti tekst:\n1 -> Vise 3\n2 -> Rotacija bitova u desno\n3 -> Pseudo-slucajni brojevi\nVasa opcija je: ");
				fflush(stdin);
				gets(unos);
			}while(provera2(unos)==0);
			original=fopen("original.txt","r");
			sifrant=fopen("sifrant.txt","w+");

				switch(unos[0]){
					

				//vise 3
				
				case '1':
					delay(0.7);
					kod_vise_tri(original,sifrant);
					fclose(original);
					fclose(sifrant);
					povratak_u_meni();
					break;


				//rotacija u desno

				case '2':
					delay(0.7);
					kod_rotacija_bitova(original,sifrant);
					fclose(original);
					fclose(sifrant);
					povratak_u_meni();
					break;


				//random kljucevi
				case '3':
					while((c=fgetc(original))!=EOF)
						br++;
					rewind(original);
					sifra=fopen("sifra.txt","w+");
					random(sifra,br);//kreiranje kljuceva
					rewind(sifra);

					delay(0.7);
					kod_random_vrednosti(original,sifrant,sifra);
					fclose(original);
					fclose(sifrant);
					fclose(sifra);
					povratak_u_meni();
					break;
				}
		break;

		//Dekodiranje

		case '2':



			//provera da li postoji tekst za dekodiranje

			
			sifrant=fopen("sifrant.txt","r");
			fseek(sifrant,0,SEEK_END);
			if(ftell(sifrant)==0){
				printf("\nDoslo je do greske, tekst za desifrovanje ne postoji,\nmolimo vas prvo sifrujte neki tekst!\n\n");
			}
			else{
				
				//mogucnost neogranicenog dekodiranja teksta (u slucaju da se pogresi opcija)

				do{
					printf("\nIzabrali ste opciju dekodiranja, unesite kljuc kojim cemo dekodirati tekst:\n\n1. -> Manje 3\n2. -> Rotacija bitova u desno\n3. -> Pseudo-slucajni brojevi\nVasa opcija je: ");
					fflush(stdin);
					gets(unos);
					provera2(unos);
					delay(1);
					printf("\nKodirani tekst je:\n");
					fseek(sifrant,0,SEEK_SET);
					delay(1.5);
					ispis_kodiranog_teksta(sifrant);
					printf("\nDekodiranje teksta...\n");
					rewind(sifrant);
						switch(unos[0]){
						
						//manje_tri 

						case '1':
							delay(1);
							dekod_manje_tri(sifrant);
							break;

						//rotacija bitova 

						case '2':
							delay(1);
							dekod_rotacija_bitova(sifrant);
							break;

						//random vrednosti kljuc

						case '3':
							delay(1);
							sifra=fopen("sifra.txt","r");
							dekod_random_vrednosti(sifrant,sifra);
							fclose(sifra);
							break;
						}
						
						
				}while(potvrda()==0);
				

			}
			
			break;
		

		//izlaz iz programa

		case '0':
			delay(1.5);
			printf("Program je uspesno zavrsen.\n\n\n\n");
			delay(1);
			return 0;
		
		}


	}while(1);
}