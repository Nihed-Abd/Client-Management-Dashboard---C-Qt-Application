#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QDate>
#include <QInputDialog>
#include <QSqlError>
#include "mainwindow.h"
#include "client.h"
#include <QMainWindow>
#include "mainwindow.h"
#include "QString"
#include "QDoubleValidator"



#define NAME_RX "([A-Z][a-z]*)([\\s\\\'.][A-Z][a-z]*)*"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(c.afficher());
    ui->le_id_2->setValidator(new QIntValidator(100,9999999,this)); //Modification



}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_on_pb_add_clicked_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int cin=ui->le_cin->text().toInt();
    QString metier=ui->le_metier->text();
    QString adresse=ui->le_adresse->text();
    int montant_credit=ui->le_montant_credit->text().toInt();
    int montant_abonnement=ui->le_montant_abo->text().toInt();


    client c (id,nom,prenom,cin,metier,adresse,montant_credit,montant_abonnement);

    bool test=c.ajouter();

    if (test)
    {
        //Refresh (Actualiser)
        ui->tableView->setModel(c.afficher());

        QMessageBox::information(nullptr,QObject::tr(""),
                                 QObject::tr("Ajout effectué\n"
                                             "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);


        ui->le_id->clear();
        ui->le_nom->clear();
        ui->le_prenom->clear();
        ui->le_cin->clear();
        ui->le_metier->clear();
        ui->le_adresse->clear();
        ui->le_montant_credit->clear();
        ui->le_montant_abo->clear();

    }
    else
    {

        QMessageBox::critical(nullptr,QObject::tr("ASSOCIATION EL WAFA"),
                                  QObject::tr("Ajout non effectué\n"
                                              "La référence existe déjà\n"
                                              "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);

        ui->le_id->clear();
    }
}

void MainWindow::on_actualiser_clicked()
{
     ui->tableView->setModel(c.afficher());
}




void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();

    QSqlQuery qry;

    qry.prepare("select * from CLIENT where ID='"+value+"'");
    if(qry.exec())
             {
                 while(qry.next())
                 {  ui->id_abo_2->setText(qry.value(0).toString());
                    ui->id_abo->setText(qry.value(0).toString());
                  ui->le_id_2->setText(qry.value(0).toString());
                  ui->le_nom_2->setText(qry.value(1).toString());
                  ui->le_prenom_2->setText(qry.value(2).toString());
                  ui->le_cin_2->setText(qry.value(3).toString());
                  ui->le_metier_2->setText(qry.value(4).toString());
                  ui->le_adresse_2->setText(qry.value(5).toString());
                  ui->le_montant_credit_2->setText(qry.value(6).toString());
                  ui->le_montant_abo_2->setText(qry.value(7).toString());

                 }

             }
}


void MainWindow::on_modify_clicked()
{
    client c;
    c.setid(ui->le_id_2->text().toInt());
    c.setnom(ui->le_nom_2->text());
    c.setprenom(ui->le_prenom_2->text());
    c.setcin(ui->le_cin_2->text().toInt());
    c.setmetier(ui->le_metier_2->text());
    c.setadresse(ui->le_adresse_2->text());
    c.setmontant_credit(ui->le_montant_credit_2->text().toInt());
    c.setmontant_abonnement(ui->le_montant_abo_2->text().toInt());

   bool check=c.modifier();

    if (check)
    {
        //Refresh (Actualiser)
        ui->tableView->setModel(c.afficher());


            QMessageBox::information(nullptr, QObject::tr("Smart Printing System"),
                                  QObject::tr("Modification avec succés.\n"
                                              "Cliquez sur annuler pour quitter."), QMessageBox::Cancel);



        ui->le_id_2->clear();
        ui->le_nom_2->clear();
        ui->le_prenom_2->clear();
        ui->le_cin_2->clear();
        ui->le_metier_2->clear();
        ui->le_adresse_2->clear();
        ui->le_montant_credit_2->clear();
        ui->le_montant_abo_2->clear();


    }
    else
    {

            QMessageBox::critical(nullptr, QObject::tr("Smart Printing System"),
                                  QObject::tr("Modification échouée.\n"
                                              "Cliquez sur annuler pour quitter."), QMessageBox::Cancel);

    }
}


void MainWindow::on_recherche_cin_textChanged(const QString &arg1)
{
    QString rech=ui->recherche_cin->text();
    ui->tableView->setModel(c.RechercheClient(rech));
}


void MainWindow::on_valider_abo_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

       if (!selectedIndexes.isEmpty())
       {
           QModelIndex selectedIndex = selectedIndexes.at(0); // Get the first selected index

           // Get the ID value from the selected index
           QString idValue = ui->tableView->model()->data(selectedIndex).toString();

           QSqlQuery query = c.afficherById(idValue.toInt()); // Assuming afficherById returns a QSqlQuery
           if (query.next())
           {
               QString nom = query.value(1).toString();
               QString prenom = query.value(2).toString();
               QString cin = query.value(3).toString();
               QString metier = query.value(4).toString();
               QString adresse = query.value(5).toString();
               QString montant_abonnement = query.value(7).toString();

               // You can retrieve other attributes in a similar way

               // Now, display the retrieved information in your UI elements
               ui->nom_abo->setText(nom);
               ui->prenom_abo->setText(prenom);
               ui->cin_abo->setText(cin);
               ui->metier_abo->setText(metier);
               ui->adresse_abo->setText(adresse);
               ui->montant_abo_abo->setText(montant_abonnement);

               // Display other attributes in corresponding UI elements
           }
           else
           {
               // Handle the case where the query didn't retrieve any data
           }

}
}

void MainWindow::on_valider_commision_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

       if (!selectedIndexes.isEmpty())
       {
           QModelIndex selectedIndex = selectedIndexes.at(0); // Get the first selected index

           // Get the ID value from the selected index
           QString idValue = ui->tableView->model()->data(selectedIndex).toString();

           QSqlQuery query = c.afficherById(idValue.toInt()); // Assuming afficherById returns a QSqlQuery
           if (query.next())
           {
               QString nom = query.value(1).toString();
               QString prenom = query.value(2).toString();
               QString cin = query.value(3).toString();
               QString metier = query.value(4).toString();
               QString adresse = query.value(5).toString();
               int montant_credit = query.value(6).toInt();
               double montant_commision = montant_credit * 2.5 / 100.0;


               // You can retrieve other attributes in a similar way

               // Now, display the retrieved information in your UI elements
               ui->nom_abo_2->setText(nom);
               ui->prenom_abo_2->setText(prenom);
               ui->cin_abo_2->setText(cin);
               ui->metier_abo_2->setText(metier);
               ui->adresse_abo_2->setText(adresse);
               ui->montant_commision->setText(QString::number(montant_commision, 'f', 2));

               // Display other attributes in corresponding UI elements
           }
           else
           {
               // Handle the case where the query didn't retrieve any data
           }

}
}


void MainWindow::on_pdf1_clicked()
{
    QPdfWriter pdf("C:/nihed/abonnement.pdf");
    QPainter painter(&pdf);
    int y = 4000; // Vertical position for attribute values

    QColor blackColor(Qt::black); // Define black color
    painter.setPen(blackColor); // Set the pen color to black

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();

    // Draw headers in Arabic
    painter.drawText(350, 500, QString::fromUtf8("Gouvernnorat de Kebili"));
    painter.drawText(370, 750, QString::fromUtf8("Délégation DOUZ NORD"));
    painter.drawText(300, 1000, QString::fromUtf8("Association De Développement ElWafa"));

    painter.drawText(8050, 500, QString::fromUtf8("ولاية قبلي"));
    painter.drawText(7700, 750, QString::fromUtf8("منطقة دوز الشمالية"));
    painter.drawText(7700, 1000, QString::fromUtf8("جمعية تنمية الوفاء"));


    painter.drawText(2300, 3250, QString::fromUtf8("دوز في "));
    painter.drawText(1000,3250,cd.toString("dd/MM/yyyy"));

    painter.drawText(600, 3800, QString::fromUtf8("امضاء المدير التنفيذي"));
    painter.drawText(900, 4100, QString::fromUtf8("معز بنعمر"));



    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        QModelIndex selectedIndex = selectedIndexes.at(0);
        QString idValue = ui->tableView->model()->data(selectedIndex).toString();
        QSqlQuery query = c.afficherById(idValue.toInt());

        while (query.next())
        {
            painter.drawLine(100, y, 9490, y);

            painter.setFont(QFont("Arial", 11));
            painter.setPen(Qt::black);

            QString id = query.value(0).toString();
            QString nom = query.value(1).toString();
            QString prenom = query.value(2).toString();
            QString cin = query.value(3).toString();
            QString metier = query.value(4).toString();
            QString adresse = query.value(5).toString();
            QString montant_abonnement = query.value(7).toString();

            int x = 6500;
            int y= 2500;// Horizontal position for attribute values
            painter.drawText(x, y, id);
            y += 250; // Move to the next attribute position
            painter.drawText(x, y, nom);
            y += 250;
            painter.drawText(x, y, prenom);
            y += 250;
            painter.drawText(x, y, cin);
            y += 250;
            painter.drawText(x, y, metier);
            y += 250;
            painter.drawText(x, y, adresse);
            y += 250;
            painter.drawText(x, y, montant_abonnement);
        }
    }

    painter.setFont(QFont("Arial", 12));
    painter.setPen(Qt::black);

    // Draw attribute names in Arabic
    painter.drawText(8100, 2500, QString::fromUtf8("المعرف"));
    painter.drawText(8150, 2750, QString::fromUtf8("الاسم"));
    painter.drawText(8150, 3000, QString::fromUtf8("اللقب"));
    painter.drawText(8100, 3250, QString::fromUtf8("رقم ب.ت"));
    painter.drawText(8150, 3500, QString::fromUtf8("المهنة"));
    painter.drawText(8150, 3750, QString::fromUtf8("العنوان"));
    painter.drawText(8050, 4000, QString::fromUtf8("مبلغ الاشتراك"));

    // Draw borders and rectangles as needed
    int imageWidth = 1500; // Adjust the width of the image
       int imageHeight = 1500; // Adjust the height of the image

painter.drawLine(100, imageHeight + 100, pdf.width() - 100, imageHeight + 100);
       // Load and draw the image
       QImage image(":/Resources/../Nouveau dossier (2)/nihed/logo.png"); // Replace with the actual image path
       painter.drawImage(4500,0, image.scaled(imageWidth, imageHeight, Qt::KeepAspectRatio));

    // End painting
    painter.end();

    int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/nihed/abonnement.pdf"));
    }
}

void MainWindow::on_pdf2_clicked()
{
    QPdfWriter pdf("C:/nihed/abonnement.pdf");
    QPainter painter(&pdf);
    int y = 4000; // Vertical position for attribute values

    QColor blackColor(Qt::black); // Define black color
    painter.setPen(blackColor); // Set the pen color to black

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();

    // Draw headers in Arabic
    painter.drawText(350, 500, QString::fromUtf8("Gouvernnorat de Kebili"));
    painter.drawText(370, 750, QString::fromUtf8("Délégation DOUZ NORD"));
    painter.drawText(300, 1000, QString::fromUtf8("Association De Développement ElWafa"));

    painter.drawText(8050, 500, QString::fromUtf8("ولاية قبلي"));
    painter.drawText(7700, 750, QString::fromUtf8("منطقة دوز الشمالية"));
    painter.drawText(7700, 1000, QString::fromUtf8("جمعية تنمية الوفاء"));


    painter.drawText(2300, 3250, QString::fromUtf8("دوز في "));
    painter.drawText(1000,3250,cd.toString("dd/MM/yyyy"));

    painter.drawText(600, 3800, QString::fromUtf8("امضاء المدير التنفيذي"));
    painter.drawText(900, 4100, QString::fromUtf8("معز بنعمر"));



    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        QModelIndex selectedIndex = selectedIndexes.at(0);
        QString idValue = ui->tableView->model()->data(selectedIndex).toString();
        QSqlQuery query = c.afficherById(idValue.toInt());

        while (query.next())
        {
            painter.drawLine(100, y, 9490, y);

            painter.setFont(QFont("Arial", 11));
            painter.setPen(Qt::black);

            QString id = query.value(0).toString();
            QString nom = query.value(1).toString();
            QString prenom = query.value(2).toString();
            QString cin = query.value(3).toString();
            QString metier = query.value(4).toString();
            QString adresse = query.value(5).toString();
            int montant_credit = query.value(6).toInt();
            double montant_commision = montant_credit * 2.5 / 100.0;

            int x = 6500;
            int y= 2500;// Horizontal position for attribute values
            painter.drawText(x, y, id);
            y += 250; // Move to the next attribute position
            painter.drawText(x, y, nom);
            y += 250;
            painter.drawText(x, y, prenom);
            y += 250;
            painter.drawText(x, y, cin);
            y += 250;
            painter.drawText(x, y, metier);
            y += 250;
            painter.drawText(x, y, adresse);
            y += 250;
            painter.drawText(x, y,  QString::number(montant_commision));
        }
    }

    painter.setFont(QFont("Arial", 12));
    painter.setPen(Qt::black);

    // Draw attribute names in Arabic
    painter.drawText(8100, 2500, QString::fromUtf8("المعرف"));
    painter.drawText(8150, 2750, QString::fromUtf8("الاسم"));
    painter.drawText(8150, 3000, QString::fromUtf8("اللقب"));
    painter.drawText(8100, 3250, QString::fromUtf8("رقم ب.ت"));
    painter.drawText(8150, 3500, QString::fromUtf8("المهنة"));
    painter.drawText(8150, 3750, QString::fromUtf8("العنوان"));
    painter.drawText(8050, 4000, QString::fromUtf8("مبلغ العمولة"));

    // Draw borders and rectangles as needed
    int imageWidth = 1500; // Adjust the width of the image
       int imageHeight = 1500; // Adjust the height of the image

painter.drawLine(100, imageHeight + 100, pdf.width() - 100, imageHeight + 100);
       // Load and draw the image
       QImage image(":/Resources/../Nouveau dossier (2)/nihed/logo.png"); // Replace with the actual image path
       painter.drawImage(4500,0, image.scaled(imageWidth, imageHeight, Qt::KeepAspectRatio));

    // End painting
    painter.end();

    int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/nihed/abonnement.pdf"));
    }
}
