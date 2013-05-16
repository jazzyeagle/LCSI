#ifndef SQLDELEGATE_H
#define SQLDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QtWebKitWidgets/QWebView>
#include "webbrowser.h"

class SQLDelegate : public QStyledItemDelegate {
    Q_OBJECT

    public:
        explicit SQLDelegate(QObject *parent = 0);
        QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void     updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    signals:
    
    public slots:
        void     onWebPageclick(QUrl url);
};

#endif // SQLDELEGATE_H
