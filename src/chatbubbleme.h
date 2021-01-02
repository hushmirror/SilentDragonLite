// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef CHATBUBBLEME_H
#define CHATBUBBLEME_H

#include <QWidget>

namespace Ui {
class ChatBubbleMe;
}

class ChatBubbleMe : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBubbleMe(QWidget *parent = nullptr);
    ~ChatBubbleMe();

private:
    Ui::ChatBubbleMe *ui;
};

#endif // CHATBUBBLEME_H
