#include "sqldelegate.h"
#include <QMessageBox>

SQLDelegate::SQLDelegate(QObject *parent) : QStyledItemDelegate(parent) {

}

QWidget* SQLDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option);

    if(index.column()==9 || index.column()==10) {
        QWebView *wv = new QWebView(parent);
        QString wvalue = index.model()->data(index, Qt::EditRole).toString();
//        QMessageBox qmb; qmb.setText(QString("%1 (%2, %3)").arg(wvalue).arg(index.row()).arg(index.column())); qmb.exec();
        QString tempvalue;
        if(wvalue != "N/A") {
            if(index.column()==9) {  // Flattr
                tempvalue = "<a href=\"http://flattr.com/thing/";
                tempvalue += wvalue;
                tempvalue += "\" target=\"_blank\"><img src=\"http://api.flattr.com/button/flattr-badge-large.png\" title=\"Flattr this\" border=\"0\" /></a>";
          } else /* column == 10 */ { // PayPal
                tempvalue = "<HTML><BODY><P>Not yet implemented</P></BODY></HTML>";
            }
            wv->setHtml(tempvalue);
            wv->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
            connect(wv, SIGNAL(linkClicked(QUrl)), this, SLOT(onWebPageclick(QUrl)));
        }
        return wv;
    } else {
        QLineEdit *le = new QLineEdit(parent);
        le->setFrame(true);
        return le;
    }
}

void     SQLDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

void     SQLDelegate::onWebPageclick(QUrl url) {
    WebBrowser *web = new WebBrowser(0, url);
    web->show();
}
