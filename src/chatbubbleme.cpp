// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#include "chatbubbleme.h"
#include "ui_chatbubbleme.h"

ChatBubbleMe::ChatBubbleMe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBubbleMe)
{
    ui->setupUi(this);
}

ChatBubbleMe::~ChatBubbleMe()
{
    delete ui;
}
