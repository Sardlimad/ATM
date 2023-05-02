#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

// Denominaciones de billetes
int MoneyDenom[5] = {50, 100, 200, 500, 1000};

// Disponibilidad de billetes
int MoneyATM[5] = {10, 10, 10, 10, 10};

// Dinero Inicial del Cliente
float clientMoney = 10500.67;

// Calcular el Total de dinero en el cajero
float TotalATM()
{
    float total;

    for (int i = 0; i < 5; i++)
    {
        total += MoneyATM[i] * MoneyDenom[i];
    }
    return total;
}

// Para tomar desiciones con tecla S o N
bool Choice()
{
    char key = getch(); // Capturar la tecla pulsada por el usuario

    if (key == 83 || key == 115)
        return true;

    return false;
}

// Consultar disponibilidad de billetes en el cajero
void StockATM()
{
    system("cls"); // Limpiar Pantalla
    cout << "*********Stock del Cajero*********" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << "$" << MoneyDenom[i] << ": " << MoneyATM[i] << endl;
    }

    cout << "----------------------------" << endl;
    cout << "Total: " << TotalATM() << endl;
}

// Abastecer cajero
void FeedATM()
{
    system("cls"); // Limpiar Pantalla
    cout << "*********Abastecer Cajero*********" << endl;

    int feed[5]; // Guardar la cantidad de billetes de cada denominacion

    // Pedir que se entren las cantidades de cada denominacion
    for (int i = 0; i < 5; i++)
    {
        cout << "$" << MoneyDenom[i] << ": ";
        cin >> feed[i];
    }

    cout << "**********************************" << endl;
    cout << "Desea ejecutar la accion? S/N Default: N" << endl;
    // Decidir si ejecutar la accion
    if (Choice())
    {
        for (int i = 0; i < 5; i++)
        {
            MoneyATM[i] += feed[i];
        }
    }
}

// Recargar cuenta del cliente
void FeedClient()
{
    system("cls"); // Limpiar pantalla
    cout << "******Recargar Cuenta Cliente******" << endl;
    cout << "Saldo Actual: " << clientMoney << endl;

    cout << "Cant. Deposito: ";
    // Monto del deposito
    float deposit;
    cin >> deposit;

    // Se realiza el deposito
    clientMoney += deposit;

    cout << "-----------------------------------" << endl;
    cout << "Deposito Realizado -- Saldo Actual: " << clientMoney << endl;
}

// Desglosar el monto a extraer segun denominaciones disponibles y devolver si queda resto que no puede ser extraido
float BreakDown(float monto)
{
    int desglose[5] = {0, 0, 0, 0, 0}; // Guardar el desglose

    cout << "-----------------------" << endl;

    for (int i = 4; i >= 0; i--)
    {
        while (monto >= MoneyDenom[i] && MoneyATM[i] > 0)
        {
            desglose[i]++;
            MoneyATM[i]--;
            monto -= MoneyDenom[i];
        }

        // Mostrar el desglose de la extraccion
        if (desglose[i] != 0)
            cout << "$" << MoneyDenom[i] << ": " << desglose[i] << endl;
    }
    // si existe resto
    if (monto != 0 && monto > 0)
        cout << "No puede ser extraido " << monto << " cup. Disculpe las molestias ocasionadas" << endl;

    return monto; // Se retorna lo sobrante, que no puede ser extraido
}

// Extraccion de Efectivo
void DebitClient()
{
    system("cls"); // Limpiar pantalla
    cout << "******Extraer Efectivo******" << endl;
    cout << "Saldo Actual: " << clientMoney << endl;

    float total = TotalATM(); // Total de dinero en el cajero

    // Si el cajero tiene dinero...proceder
    if (total != 0)
    {

        cout << "Cant. Extraer: ";
        // Monto de la extraccion
        float debit;
        cin >> debit;

        if (debit <= total && debit <= clientMoney)
        {
            // Se realiza el desglose y se resta de la cuenta del usuario lo que puede ser extraido
            clientMoney -= (debit - BreakDown(debit));
        }
        else if (debit > clientMoney)
        {
            cout << "---SALDO de CUENTA INSUFICIENTE---" << endl;

        }
        else
        {
            cout << "No hay disponibilidad para el monto especificado." << endl;
            cout << "Desea extraer " << total << " ? S/N Default: N" << endl;
            if (Choice())
            {
                clientMoney -= total - BreakDown(total);
            }
        }

        // si el cajero no tiene dinero
    }
    else
    {
        cout << "---CAJERO SIN EFECTIVO---" << endl;
    }
}

// Salida
void ExitATM()
{
    system("cls"); // Para limpiar la pantalla

    cout << "Seguro que desea salir? S/N Default: N" << endl;
    if (Choice())
        exit(0);
}

// Menu Principal
void menuATM()
{
    char key; // Para almacenar la tecla pulsada por el usuario

    // Ciclo Infinito para siempre regresar al menu de opciones
    while (true)
    {
        system("cls"); // Para limpiar la pantalla cada vez que se selecciona una opcion

        // Menu de Opciones
        cout << "*********OPCIONES BANCO*********" << endl;
        cout << "(A) Abastecer Cajero" << endl;
        cout << "(B) Stock del Cajero" << endl;
        cout << "(C) Recargar Cuenta Cliente" << endl;
        cout << "********************************" << endl;
        cout << " " << endl;
        cout << "********OPCIONES CLIENTE********" << endl;
        cout << "(D) Extraer Efectivo" << endl;
        cout << "(X) Salir" << endl;
        cout << "********************************" << endl;

        // Capturar la tecla pulsada por el usuario
        key = getch();

        // Realizar una accion segun desee el usuario.
        switch (key)
        { // Se idientifica la tecla presionada por su codigo ASCII

        case 65:
            FeedATM();
            break; // Tecla A y a
        case 97:
            FeedATM();
            break;

        case 66:
            StockATM();
            break; // Tecla B y b
        case 98:
            StockATM();
            break;

        case 67:
            FeedClient();
            break; // Tecla C y c
        case 99:
            FeedClient();
            break;

        case 68:
            DebitClient();
            break; // Tecla D y D
        case 100:
            DebitClient();
            break;

        case 88:
            ExitATM();
            break; // Tecla X y x
        case 120:
            ExitATM();
            break;

        default:
            break;
        }

        cout << "****Presiones una tecla para volver al MENU****" << endl;
        getch();
    }
}

int main()
{
    menuATM();

    return 0;
}
