#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QDialog>

namespace Ui {
class WebBrowser;
}

class WebBrowser : public QDialog
{
    Q_OBJECT
    
public:
    explicit WebBrowser(QWidget *parent, QUrl url);
    ~WebBrowser();
    
private:
    Ui::WebBrowser *ui;

public slots:
    void onLoadFinished(bool ok);
};

#endif // WEBBROWSER_H
