#ifndef ADDDIALOG_AV_H
#define ADDDIALOG_AV_H

#include "View/adddialog_docs.h"


/*! \brief Avdialog class for representing (input/output) of AV document information
 *
 *  This class is inherited from the general documents dialog which has all common feature along with the addition attributes represented in AV
 *
 */
class AddDialog_av : public AddDialog_docs
{
    Q_OBJECT

public:
    AddDialog_av(QWidget *parent, int id); //!< constructor of the empty input of AV information along with the id of the new AV we wish to add
    AddDialog_av(QWidget *parent, AV *newAv, int pMode, User *U); //!< constructor of the dialog that represents information of the AV document we wish to view/edit
    AddDialog_av(QWidget *parent); //!< default constructor

    void setDocument(Document *doc); //!< a function that sets the dialog fields according to a certain AV document
    Document *getDocument(); //!< a function that gets all information from the dialog and normalize it as an AV object

protected:
    bool validate(); //!< dialog input validator

};

#endif // AV_ADDDIALOG_H
