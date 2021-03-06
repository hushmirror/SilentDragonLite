// Copyright 2019-2021 The Hush developers
// Released under the GPLv3

#include "Chat.h"
#include "../addressbook.h"
#include "../DataStore/DataStore.h"
Chat::Chat() {}

ChatMemoEdit::ChatMemoEdit(QWidget* parent) : QTextEdit(parent) {
    QObject::connect(this, &QTextEdit::textChanged, this, &ChatMemoEdit::updateDisplayChat);
}

void ChatMemoEdit::updateDisplayChat() {
    QString txt = this->toPlainText();
    if (lenDisplayLabelchat)
        lenDisplayLabelchat->setText(QString::number(txt.toUtf8().size()) + "/" + QString::number(maxlenchat));

    if (txt.toUtf8().size() <= maxlenchat) {
        // Everything is fine
        if (sendChatButton)
            sendChatButton->setEnabled(true);

        if (lenDisplayLabelchat)
            lenDisplayLabelchat->setStyleSheet("");
    } else {
        // Overweight
        if (sendChatButton)
            sendChatButton->setEnabled(false);

        if (lenDisplayLabelchat)
            lenDisplayLabelchat->setStyleSheet("color: red;");
    }
}

void ChatMemoEdit::setMaxLenChat(int len) {
    this->maxlenchat = len;
    updateDisplayChat();
}

void ChatMemoEdit::SetSendChatButton(QPushButton* button) {
    this->sendChatButton = button;
}

void ChatMemoEdit::setLenDisplayLabelChat(QLabel* label) {
    this->lenDisplayLabelchat = label;
}

ChatMemoEditRequest::ChatMemoEditRequest(QWidget* parent) : QTextEdit(parent) {
    QObject::connect(this, &QTextEdit::textChanged, this, &ChatMemoEditRequest::updateDisplayChatRequest);
}


// TODO: unify this with updateDisplayChat()
void ChatMemoEditRequest::updateDisplayChatRequest() {
    QString txt = this->toPlainText();
    if (lenDisplayLabelchatRequest)
        lenDisplayLabelchatRequest->setText(QString::number(txt.toUtf8().size()) + "/" + QString::number(maxlenchatrequest));

    if (txt.toUtf8().size() <= maxlenchatrequest) {
        // Everything is fine
        if (sendRequestButton)
            sendRequestButton->setEnabled(true);

        if (lenDisplayLabelchatRequest)
            lenDisplayLabelchatRequest->setStyleSheet("");
    } else {
        // Overweight
        if (sendRequestButton)
            sendRequestButton->setEnabled(false);

        if (lenDisplayLabelchatRequest)
            lenDisplayLabelchatRequest->setStyleSheet("color: red;");
    }
}

void ChatMemoEditRequest::setMaxLenChatRequest(int len) {
    this->maxlenchatrequest = len;
    updateDisplayChatRequest();
}

void ChatMemoEditRequest::SetSendRequestButton(QPushButton* button) {
    this->sendRequestButton = button;
}

void ChatMemoEditRequest::setLenDisplayLabelChatRequest(QLabel* label) {
    this->lenDisplayLabelchatRequest = label;
}

void Chat::renderChatBox(Ui::MainWindow *ui, QListView *view, QLabel *label)
{
    
    QStandardItemModel *chat = new QStandardItemModel();
    DataStore::getChatDataStore()->dump(); // test to see if the chat items in datastore are correctly dumped to json
    std::map<QString,int> seenTxids;

    qDebug() << __func__ << ": looking at memos...";
    for (auto &contact : AddressBook::getInstance()->getAllAddressLabels())
    {
        for (auto &memo : DataStore::getChatDataStore()->getAllMemos()) {
            if ( (contact.getName() == ui->contactNameMemo->text().trimmed()) &&
                (contact.getPartnerAddress() == memo.second.getAddress()) &&
                (memo.second.isOutgoing() == true)) {

                QStandardItem *Items = new QStandardItem(memo.second.toChatLine());

                Items->setData(OUTGOING, Qt::UserRole + 1);
                qDebug() << __func__ << ": appending row to OUTGOING chatitems to contact " << contact.getName() << " with item " << Items;
                chat->appendRow(Items);
                ui->listChat->setModel(chat);
       
            } else {
                ui->listChat->setModel(chat);
            }

            qDebug() << __func__ << ": memo.first=" << memo.first;
            if ( (contact.getName() == ui->contactNameMemo->text().trimmed()) &&
                (contact.getMyAddress() == memo.second.getAddress()) &&
                (memo.second.isOutgoing() == false) &&
                (memo.second.getCid() == contact.getCid())
                ) {
                QStandardItem *Items1 = new QStandardItem(memo.second.toChatLine());
                Items1->setData(INCOMING, Qt::UserRole + 1);
                qDebug() << __func__ << ": appending row to INCOMING chatitems to contact " << contact.getName() << "with txid=" << memo.second.getTxid() << " cid=" << contact.getCid() << " item " << Items1 << " memo=" << memo.second.getMemo();


                if(seenTxids.count( memo.second.getTxid() ) > 0) {
                    // Do not render the same chat multiple times
                    // TODO: this should also look at outputindex to allow for multi-part memos, when that is supported
                    qDebug() << __func__ << ": INCOMING ignoring txid=" << memo.second.getTxid();
                    continue;
                }

                // TODO: better header memo detection
                if (memo.second.getMemo().startsWith("{")) {
                    qDebug() << __func__ << ": ignoring header memo=" << memo.second.getMemo();
                } else {
                    chat->appendRow(Items1);
                    ui->listChat->setModel(chat);
                    ui->memoTxtChat->setEnabled(true);
                    ui->emojiButton->setEnabled(true);
                    ui->sendChatButton->setEnabled(true);

                    seenTxids[ memo.second.getTxid() ] = 1;
                }
               
            } else {
                ui->listChat->setModel(chat);
            }
        }
    } 
}  

