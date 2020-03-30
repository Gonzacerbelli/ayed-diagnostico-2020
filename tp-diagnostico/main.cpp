#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct Branch {
    int id;
    char address[50];
    string zone;
    float billing;
};

std::vector<Branch> branches;
int lastId = 0;
void menu();

int branchesLength(){
    return branches.size();
};

void exit(){
    cout << "\n\nGracias por usar el Sistema de Gestion" << endl;
};

void backMenuQuestion(){
    int option;
    cout << "\n¿Quiere volver al menu?\n1.Volver al menu\n2.Salir\n\nIngrese una opcion: ";
    fflush(stdin);
    cin >> option;

    while(option < 1 || option > 2){
        cout << "\nOpcion incorrecta, por favor elija una opcion nuevamente nuevamente:\n1.Volver al menu\n2.Salir\n\nIngrese una opcion: ";
        fflush(stdin);
        cin >> option;
    };

    if(option == 1){
        menu();
    } else if(option == 2){
        exit();
    }
};

bool verifyUsedBranchId(int branchId){
    bool used = false;
    if(branchesLength() != 0) {
        int i;
        for (i = 0; i < branchesLength(); i++){
            if(branches[i].id == branchId){
                used = true;
            }
        }
    }
    cout << "used: " << used << endl;
    return used;
};

float getZoneBillingTotal(string zone){
    int i;
    float totalBilling = 0;

    for(i = 0; i < branches.size(); i++){
        if(branches[i].zone == zone){
            totalBilling += branches[i].billing;
        }
    }
    return totalBilling;
};

string chooseAndGetZone(){
    int zoneId;
    string zone;

    cout << "\nElija una zona:\n1.Zona Norte\n2.Zona Sur\n3.Zona Este\n4.Zona Oeste\n5.Zona Centro\n\nIngrese una opcion: ";
    fflush(stdin);
    cin >> zoneId;

    while(zoneId < 1 || zoneId > 5){
        cout << "\nZona incorrecta, por favor elija una zona nuevamente:\n1.Zona Norte\n2.Zona Sur\n3.Zona Este\n4.Zona Oeste\n5.Zona Centro\n\nIngrese una opcion: ";
        fflush(stdin);
        cin >> zoneId;
    };

    switch(zoneId){
        case 1: zone = "Zona Norte";
        break;
        case 2: zone = "Zona Sur";
        break;
        case 3: zone = "Zona Este";
        break;
        case 4: zone = "Zona Oeste";
        break;
        case 5: zone = "Zona Centro";
        break;
    };
    return zone;
}

void dataEntry(){
    cout << "\nIngreso de sucursales" << endl;
    if(branchesLength() < 24 || lastId == 1000){
        int i, branchId, option;
        bool usedId;
        Branch newBranch;

        cout << "\nIngrese un ID: ";
        fflush(stdin);
        cin >> branchId;

        usedId = verifyUsedBranchId(branchId);

        while(usedId){
            cout << "\nID " << branchId << " en uso, intente con otro.";
            cout << "\n\nIngrese un ID: ";
            fflush(stdin);
            cin >> branchId;
            usedId = verifyUsedBranchId(branchId);
        };

        if (branchId == 1000){
            cout << "\nSe ingreso el ID 1000, carga terminada." << endl;
            lastId = branchId;
            menu();
        }
        else if (branchId < 100 || (branchId > 999 && branchId != 1000)) {
            cout << "\nEl ID debe ser mayor a 100 y menor a 999" << endl;
            dataEntry();
        } else {
            newBranch.id = branchId;

            cout << "\nIngrese una direccion: ";
            fflush(stdin);
            cin.get(newBranch.address, 50);

            newBranch.zone = chooseAndGetZone();

            cout << "\nIngrese la facturacion: ";
            fflush(stdin);
            cin >> newBranch.billing;

            branches.push_back(newBranch);

            newBranch = {};

            cout << "\n¿Quiere agregar otra sucursal?\n1.Agregar otra sucursal\n2.Volver al menu\n3.Salir\n\nIngrese una opcion: ";
            fflush(stdin);
            cin >> option;

            while(option < 1 || option > 3){
                cout << "\nOpcion incorrecta, por favor elija una opcion nuevamente nuevamente:\n1.Agregar otra sucursal\n2.Volver al menu\n3.Salir\n\nIngrese una opcion: ";
                fflush(stdin);
                cin >> option;
            };

            switch(option){
                case 1: dataEntry();
                break;
                case 2: menu();
                break;
                case 3: exit();
                break;
            }
        }
    } else {
        cout << "Límite de 25 sucursales alcanzado o carga finalizada manualmente.";
    }
};

void billingList(){
    if(branches.size() == 0){
        cout << "\nNo posee sucursales ingresadas. Por favor ingrese sucursales." << endl;
        menu();
    } else {
        float southTotal = getZoneBillingTotal("Zona Sur"),
            northTotal = getZoneBillingTotal("Zona Norte"),
            eastTotal = getZoneBillingTotal("Zona Este"),
            westTotal = getZoneBillingTotal("Zona Oeste"),
            centerTotal = getZoneBillingTotal("Zona Centro");

        cout << "\nListado de facturacion por zona" << endl;
        cout << "\nEl total de facturacion de la Zona Sur es de: " << southTotal << endl;
        cout << "\nEl total de facturacion de la Zona Norte es de: " << northTotal << endl;
        cout << "\nEl total de facturacion de la Zona Este es de: " << eastTotal << endl;
        cout << "\nEl total de facturacion de la Zona Oeste es de: " << westTotal << endl;
        cout << "\nEl total de facturacion de la Zona Centro es de: " << centerTotal << endl;
        backMenuQuestion();
    }
};

void maxMinBilling(){
    if(branches.size() == 0){
        cout << "\nNo posee sucursales ingresadas. Por favor ingrese sucursales." << endl;
        menu();
    } else {
        int i, maxId = 0, maxBilling = 0, minId = branches[0].id, minBilling = branches[0].billing;
        char maxAddress[50], minAddress[50];
        strncpy(minAddress, branches[0].address, 50);
        string maxZone, minZone = branches[0].zone;

        for(int i = 0; i < branches.size(); i++){
            if(branches[i].billing > maxBilling){
                maxBilling = branches[i].billing;
                maxId = branches[i].id;
                strncpy(maxAddress, branches[i].address, 50);
                maxZone = branches[i].zone;
            } else if(branches[i].billing < minBilling){
                minBilling = branches[i].billing;
                minId = branches[i].id;
                strncpy(minAddress, branches[i].address, 50);
                minZone = branches[i].zone;
            }
        }

        cout << "\nLa sucursal con ID " << maxId << ", en " << maxZone << " y direccion " << maxAddress << " tuvo la facturacion maxima de " << maxBilling << endl;
        cout << "\nLa sucursal con ID " << minId << ", en " << minZone << " y direccion " << minAddress << " tuvo la facturacion minima de " << minBilling << endl;

        backMenuQuestion();
    }
};

void verifyMenu(int option){
    switch(option){
        case 1: dataEntry();
        break;
        case 2: billingList();
        break;
        case 3: maxMinBilling();
        break;
        case 4: exit();
        break;
        default:
            cout << "\nIngreso una opcion incorrecta, pruebe de nuevo." << endl;
            menu();
        break;
    }
};

void menu(){
    int option;
    cout << "\nMenu" << endl;
    cout << "Elija el numero de la opcion:" << endl;
    cout << "1.Carga de informacion" << endl;
    cout << "2.Listado de facturacion por zona" << endl;
    cout << "3.Maximo y minimo de facturacion" << endl;
    cout << "4.Salir" << endl;
    cout << "\nIngrese opcion: ";
    cin >> option;

    verifyMenu(option);
};

int main(){
    cout << "Bienvenido al Sistema de Gestion" << endl;
    menu();
    return 0;
};
