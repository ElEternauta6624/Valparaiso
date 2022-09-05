#include <iostream>
#include <fstream>

using namespace std;

void viajes (int lotes[][5], int &entregas, int promprod, int fils){
for(int i = 0; i<fils; i++){
    entregas += lotes[i][promprod];
}
}

void BoB(bool checkV[][5], double distG[][5], int list[], int &Mcliente, int fils, int cols){
int Mclientecheck = 0;
 for (int i=0; i<fils; i++){
        int fig = 0;
         for(int j=0; j<cols; j++){
            if(checkV[i][j]){
                fig++;
            }
         }
    if(fig > Mclientecheck){
        Mclientecheck = fig;
        Mcliente = i;
    }
 }
 list[0] = 0;
 for(int prom=1; prom<cols; prom++){
    int i = prom-1;
    while (i>=0 && distG[Mcliente][prom] < distG[Mcliente][list[i]]){
        list[i+1] = list[i];
        i--;
    }
    list[i+1] = prom;
 }
}


void lista(double matrix[][5], bool checkV[][5], int rows, int cols){

for(int i =0; i<rows; i++){
    for(int j=0; j<cols; j++){
        if (matrix[i][j] > 13000){
            checkV[i][j]=true;
        }
    }
}
}

int main()
{
    int noms {8};
	int prods {5};
	double uniprod[noms][5] {};
	int lotes[noms][5] {};
	double distG[noms][5] {};
	int numUnits[noms][5] {};

	string nombres[noms];
	string productoS[prods];

	ifstream archilec;
	archilec.open("Nombres.txt");
	if (!archilec){
        cout << "ERROR" << endl;
		return 1;
	}
	for (int i = 0; i < noms && archilec >> nombres[i]; ++i);
	for (int i = 0; i < prods && archilec >> productoS[i]; ++i);
	archilec.close();

	archilec.open("Datos.txt");
	if (!archilec) {
		cout << "ERROR" << endl;
		return 1;
	}
	int iprod, inom;
	double cant, kms;
	while (archilec >> inom >> iprod >> cant >> kms) {
		uniprod[inom][iprod] += cant;
		distG[inom][iprod] += kms;
		lotes[inom][iprod]++;
		numUnits[inom][iprod] += cant;
	}
	archilec.close();
	cout << endl;

	bool checkV[noms][5] {};
	lista(uniprod, checkV, noms, prods);
	cout << "Los articulos que los clientes cuyos pesos superaron los 13000 kgs son :" << endl;
	for (int i=0; i<noms; i++){
            cout << nombres[i] << ": ";
        bool Pri = true;
        for (int j=0; j<prods; j++){
            if(checkV[i][j] && Pri){
                cout << productoS[j];
                Pri = false;
            }
            else if (checkV[i][j]){
                cout << ", " << productoS[j];
            }
        }
        cout << "." << endl;
	}
	cout << endl;

	int Mcliente {}, list[prods] {};
	BoB(checkV, distG, list, Mcliente, noms, prods);
	cout << "El cliente " << nombres[Mcliente] << " pidio los siguientes productos y recorrieron los marcados kilometros que se mostraran de manera asendente: " << endl;
	for(int j=0; j<prods; j++){
        cout << productoS[list[j]] << ": " << distG[Mcliente][list[j]] << " KMs" << endl;
	}
	cout << endl;


	int entregas {};
	viajes(lotes, entregas, list[prods-1], noms);
	cout << "Los productos del cliente " << nombres[Mcliente] << " que mas recorrienron fueron: " << productoS[list[prods-1]] << endl;
	cout << "Y se han hecho " << entregas << " entregas" << endl;
	cout << endl;

    return 0;
}
