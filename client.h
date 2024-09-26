#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class client
{
    QString nom,prenom,metier,adresse;
    int id,cin,montant_credit,montant_abonnement;

public:
    //Constructeurs
    client();
    client(int,QString,QString,int,QString,QString,int,int);

    //Getters
    int getid(){return id;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getcin(){return cin;}
    QString getmetier(){return metier;}
    QString getadresse(){return adresse;}
    int getmontant_credit(){return montant_credit;}
    int getmontant_abonnement(){return montant_abonnement;}


    //Setters
    void setid(int id_c)
    {
        id=id_c;
    }

    void setnom(QString nom_c)
    {
        nom=nom_c;
    }

    void setprenom(QString prenom_c)
    {
        prenom=prenom_c;
    }

    void setcin(int cin_c)
    {
        cin=cin_c;
    }

    void setmetier(QString metier_c)
    {
        metier=metier_c;
    }
    void setadresse(QString adresse_c)
    {
        adresse=adresse_c;
    }
    void setmontant_credit(int montant_credit_c)
    {
        montant_credit=montant_credit_c;
    }
    void setmontant_abonnement(int montant_abonnemnt_c)
    {
       montant_abonnement=montant_abonnemnt_c;
    }

    //Fonctionalités de base relatives à l'éntité client
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQuery afficherById(int);
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* RechercheClient(QString);
    QSqlQueryModel* afficherAbo(QString);





};

#endif // CLIENT_H
