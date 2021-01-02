// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#include "chatbubblepartner.h"
#include "ui_chatbubblepartner.h"

ChatBubblePartner::ChatBubblePartner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBubblePartner)
{
    ui->setupUi(this);
}

ChatBubblePartner::~ChatBubblePartner()
{
    delete ui;
}
