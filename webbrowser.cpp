#include "webbrowser.h"
#include "ui_webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent, QUrl url) : QDialog(parent), ui(new Ui::WebBrowser) {
    ui->setupUi(this);
    ui->webView->load(url);
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

WebBrowser::~WebBrowser() {
    delete ui;
}

void WebBrowser::onLoadFinished(bool ok) {
    ui->webView->setWindowTitle(ui->webView->title());
}
