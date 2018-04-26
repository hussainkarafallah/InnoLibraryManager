#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include <Model/documententity.h>
#include <Data/documentdataproxy.h>

/*! \brief Document Model which we represent information of our library documents inside
 *
 *  This class is linked to the database and it stores the information requested by the user throught the view, and is presented to the user through the view object that maintains the interface
 *  It's a table styled model.
 *
 */
class DocumentModel : public QStandardItemModel
{

    Q_OBJECT

private:
    QList<Document*> documentsList; //!< information about documents presented currently in the model
    DocumentDataProxy *ddbProxy; //!<   connection to datavbase
    void updateData(); //!< a function that updates the data in the model
    void appendDocument(Document *doc); //!< a function that adds a document to our current presented model



public:
    void filterResults(SearchSpecifier F);

    explicit DocumentModel(QObject *parent = nullptr); //!<  constructor
    int getNewId() const; //!< a function that requests a new id from the database
    int getNewCopyId() const; //!<  a function that requests a new COPY id from the database
    int deleteByIndex(QModelIndex index); //!<  a function that deletes the document the librarian referring to
    Document* getByIndex(QModelIndex index); //!<  a function that gets the information about the document the librarian referring to
    void insertDocument(Document *doc); //!<  a function that inserts a new document into the model and forwards it to the database
    void updateDocument(Document *doc); //!<  a function that updates the info of a document in the model and forwards the update to the database
public slots:


};

#endif // DOCUMENTMODEL_H
