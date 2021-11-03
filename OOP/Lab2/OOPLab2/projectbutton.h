#ifndef PROJECTBUTTON_H
#define PROJECTBUTTON_H

#include <QPushButton>

class ProjectButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ProjectButton(QWidget parent, QString button_text);

};

#endif // PROJECTBUTTON_H
