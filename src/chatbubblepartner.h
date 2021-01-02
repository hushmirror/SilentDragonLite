// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef CHATBUBBLEPARTNER_H
#define CHATBUBBLEPARTNER_H

#include <QWidget>

namespace Ui {
class ChatBubblePartner;
}

class ChatBubblePartner : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBubblePartner(QWidget *parent = nullptr);
    ~ChatBubblePartner();

private:
    Ui::ChatBubblePartner *ui;
};

#endif // CHATBUBBLEPARTNER_H
