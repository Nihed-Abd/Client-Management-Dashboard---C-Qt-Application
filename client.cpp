#include "client.h"

#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPainter>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QTextCodec>



client::client()
{

}

client::client(int id,QString nom,QString prenom,int cin,QString metier,QString adresse,int montant_credit , int montant_abonnement)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->cin=cin;
    this->metier=metier;
    this->adresse=adresse;
    this->montant_credit=montant_credit;
    this->montant_abonnement=montant_abonnement;

}
bool client::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString cin_string = QString::number(cin);
    QString montant_credit_string = QString::number(montant_credit);
    QString montant_abonnement_string = QString::number(montant_abonnement);


    //prepare() prend la requête en paramètre pour la préparer à l'exécution
    query.prepare("insert into CLIENT(ID,NOM,PRENOM,CIN,METIER,ADRESSE,MONTANT_CREDIT,MONTANT_ABONNEMENT)"
                  "values (:id,:nom,:prenom,:cin,:metier,:adresse,:montant_credit,:montant_abonnement)");

    //création des variables liées
    query.bindValue(":id",id_string);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":cin",cin_string);
    query.bindValue(":metier",metier);
    query.bindValue(":adresse",adresse);
    query.bindValue(":montant_credit",montant_credit_string);
    query.bindValue(":montant_abonnement",montant_abonnement_string);



    return query.exec();
    // exec() envoie la requete pour l'exécution
}
QSqlQueryModel * client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from CLIENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("المعرف"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("الاسم"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("اللقب"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("رقم ب.ت"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("المهنة"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("العنوان"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("القرض"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("الاشتراك"));

    return model;
}
QSqlQuery client::afficherById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE ID = ?");
    query.addBindValue(id);
    query.exec();

    return query;
}




bool client::modifier()
{
    QSqlQuery query;
    query.prepare("Update CLIENT set ID=:id,NOM=:nom,PRENOM=:prenom,CIN=:cin,METIER=:metier,ADRESSE=:adresse,MONTANT_CREDIT=:montant_credit,MONTANT_ABONNEMENT=:montant_abonnement where ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":cin",cin);
    query.bindValue(":metier",metier);
    query.bindValue(":adresse",adresse);
    query.bindValue(":montant_credit",montant_credit);
    query.bindValue(":montant_abonnement",montant_abonnement);



    return query.exec();
}





QSqlQueryModel * client::afficherAbo(QString recherche)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT WHERE CIN LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("المعرف"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("الاسم"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("اللقب"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("رقم ب.ت"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("المهنة"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("العنوان"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("القرض"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("الاشتراك"));


return model;
}

QSqlQueryModel* client::RechercheClient(QString recherche)
{
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM CLIENT WHERE CIN LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("المعرف"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("الاسم"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("اللقب"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("رقم ب.ت"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("المهنة"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("العنوان"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("القرض"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("الاشتراك"));


return model;
}














