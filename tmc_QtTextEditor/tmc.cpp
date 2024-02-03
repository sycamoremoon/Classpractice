#include "Editor.h"
#include <QtPrintSupport/QPrinter>
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Editor);
	QApplication app(argc, argv); 
	Editor My_Editor;
    My_Editor.setWindowIcon(QIcon(":/Editor/bubble.ico"));
	My_Editor.show(); 
	return app.exec(); 
}
MyDialog::MyDialog(QWidget *parent) : QDialog(parent)   //构造函数定义，将外部图像作为引用传入
{
	this->resize(240,120); //重设窗口尺寸
	this->setWindowTitle("设置行间距和页边距");//设置窗口标题
	this->setWindowFlags(Qt::Window); //设置本对话框的右上方最小化最大化关闭按钮和Window一样

    // 创建控件
    QLabel *lineSpacingLabel = new QLabel("Line Spacing:");
    lineSpacingSpinBox = new QDoubleSpinBox;
    lineSpacingSpinBox->setRange(0.5, 10.0);
    lineSpacingSpinBox->setValue(1.5);

    QLabel *marginLabel = new QLabel("Page Margin:");
    marginSpinBox = new QSpinBox;
    marginSpinBox->setRange(0, 20000);
    marginSpinBox->setValue(20);

    QPushButton *applyButton = new QPushButton("Apply");

    // 布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineSpacingLabel);
    layout->addWidget(lineSpacingSpinBox);
    layout->addWidget(marginLabel);
    layout->addWidget(marginSpinBox);
    layout->addWidget(applyButton);

    setLayout(layout);

	connect(applyButton, &QPushButton::clicked, this, &applyButtonClicked);//OK按钮点击和处理函数的连接
}


void MyDialog::applyButtonClicked()
{
	this->accept();//OK按钮点击以后发出Accepted返回值
}

void Editor::showDialog()
{
	MyDialog MyDialog(this); //定义MyDialog对象myDialog

	if (MyDialog.exec()==QDialog::Accepted) //显示myDialog，并且用于点击的是OK按钮
	{
        applySettings(MyDialog.lineSpacingSpinBox->value(),MyDialog.marginSpinBox->value());
	}
}
//定义构造函数，参数是父窗体指针，先调用基类构造函数QEditor(parent)
Editor::Editor(QWidget *parent):QMainWindow(parent)
{
    this->setWindowTitle("TMC");//设置窗口标题
 
    this->resize(1100,700);//重设窗口大小
    
    bool code = parseCommandLine();

    //创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    
    //添加菜单栏到主窗口中
    this->setMenuBar(menuBar);
    fontsize = new QComboBox();
    fontsize->setObjectName("fontsize");
    fontsize->setMaximumSize(QSize(88, 28));
    fontsize->setFocusPolicy(Qt::ClickFocus);
    fontsize->addItems({"9", "10", "11", "12","13","14","15","16","17","18","19","20",\
    "21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38",\
    "39","40","41","42","43","44","45","46","47","48","49","50"});
    fontsize->setEditable(false);
    fontsize->setCurrentText("12");    
    fontsize->setEditable(true);

    //菜单栏添加菜单
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    menuBar->addMenu(menu4);
    menuBar->addMenu(menu5);
    menuBar->addMenu(menu6);
    menuBar->addMenu(menu7);
    //文件菜单添加菜单项
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addAction(action7);
    menu1->addSeparator();//插入分割线
    menu1->addMenu(menu9);//添加二级菜单
    menu9->addAction(action19);//二级菜单添加菜单项
    menu9->addAction(action31);
    menu9->addAction(action33);
    menu9->addAction(action32);
    
    //编辑菜单添加菜单项
    menu2->addAction(action10);
    menu2->addAction(action11);
    menu2->addAction(action12);
    menu2->addAction(action13);
    menu2->addAction(action14);
    menu2->addAction(action15);
    menu2->addAction(action16);
    menu2->addAction(action17);

    //Coding菜单添加菜单项
    menu3->addAction(action35);
    menu3->addAction(action36);

    //构建菜单添加菜单项
    menu4->addAction(action38);
    menu4->addAction(action39);
    menu4->addAction(action40);

    //调试菜单添加菜单项
    menu5->addAction(action41);
    menu5->addAction(action42);
    menu5->addAction(action43);

    //工具菜单栏
    menu6->addAction(action37);

    //帮助菜单添加菜单项
    menu7->addAction(action18);

    //添加快捷键
    action1->setShortcut(QKeySequence("Ctrl+n"));//快捷键ctrl+N
    action2->setShortcut(QKeySequence("Ctrl+o"));//快捷键ctrl+O
    action3->setShortcut(QKeySequence("Ctrl+x"));//快捷键ctrl+x
    action4->setShortcut(QKeySequence("Ctrl+c"));//快捷键ctrl+c
    action5->setShortcut(QKeySequence("Ctrl+v"));//快捷键ctrl+v
    action7->setShortcut(QKeySequence("Ctrl+s"));//快捷键ctrl+s

    //设置tab键长度
    textEdit->setTabStopDistance(40);

    //主窗口添加工具栏
    this->addToolBar(Qt::TopToolBarArea,toolBar);//设置工具栏默认停靠在顶部
    
    toolBar->setFloatable(false);//设置不允许浮动
    toolBar->setMovable(false);//设置不允许移动
    // toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//设置工具项为图片在文字上方
    toolBar->setStyleSheet("background-color:rgb(255,255,255);");
    toolBar->setIconSize(QSize(20,20));


    //工具栏添加工具项
    toolBar->addAction(action3);    
    toolBar->addAction(action4);
    toolBar->addAction(action5);

    toolBar->addSeparator();//添加分割线
    toolBar->addAction(action8);    
    toolBar->addAction(action9);

    toolBar->addSeparator();//添加分割线
    toolBar->addAction(action10);
    toolBar->addAction(action15);
    toolBar->addAction(action11);    
    toolBar->addAction(action21);
    toolBar->addAction(action12);
    toolBar->addAction(action13);
    toolBar->addAction(action14);
    toolBar->addWidget(fontsize);
    toolBar->addAction(action20);

    toolBar->addSeparator();//添加分割线
    toolBar->addAction(action16);
    toolBar->addAction(action23);        
    toolBar->addAction(action17);


    toolBar->addSeparator();//添加分割线
    toolBar->addAction(action24);
    toolBar->addAction(action25);   
    toolBar->addAction(action26);
    toolBar->addAction(action27);
    toolBar->addAction(action29);
    toolBar->addAction(action30);
    toolBar->addAction(action34);

    toolBar->addSeparator();//添加分割线
    toolBar->addAction(action22);
    toolBar->addAction(action28);

    toolBar->addSeparator();//添加分割线
    
    toolBar->addAction(action6);

    status->setObjectName("状态栏");
    status->setStyleSheet("QStatusBar::item{border: 0px}"); //设置不显示label的边框
    //主窗口添加状态栏
    this->setStatusBar(status);

    //状态栏添加编码信息
    decodeButton = new QPushButton("UTF-8", this);
    decodeButton->setStyleSheet("border: none;");
    decodeButton->setMinimumSize(40, 10);  // 设置最小尺寸为宽度100，高度50
    decodeButton->setMaximumSize(100, 25); // 设置最大尺寸为宽度200，高度100
    status->addPermanentWidget(decodeButton);//添加右侧标签
 
    //状态栏添加模式信息
    status->addPermanentWidget(statusLabel);//添加右侧标签
 

    //设置中心部件
    textEdit->setFont(QFont("Consolas",12,QFont::AnyStyle));
    textEdit->setObjectName("Text Editor");

    //主窗口设置文本编辑框为中心部件
    this->setCentralWidget(textEdit);
    //设置语法高亮
    highlighter = new Highlighter();
    if(code)start_coding();
    highlighter->setDocument(textEdit->document());



/*********************************槽函数与信号的链接*******************************/
    connect(action1,&QAction::triggered,this,&on_actionne_triggered);//创建文件连接信号槽
    connect(action2,&QAction::triggered,this,&on_actionopenfile_triggered);//打开文件连接信号槽
    connect(action3,&QAction::triggered,this,&on_actioncut_triggered);
    connect(action4,&QAction::triggered,this,&on_actioncopy_triggered);
    connect(action5,&QAction::triggered,this,&on_actionpatse_triggered);    
    connect(action6,&QAction::triggered,this,&on_actionexit_triggered);
    connect(action7,&QAction::triggered,this,&on_ServeFile_triggered);
    connect(action8,&QAction::triggered,this,&on_actionundo_triggered);
    connect(action9,&QAction::triggered,this,&on_actionredo_triggered); 
    connect(action10,&QAction::triggered,this,&on_actionTextBold_triggered);
    connect(action11,&QAction::triggered,this,&on_actionTextItalic_triggered);
    connect(action12,&QAction::triggered,this,&on_actionLift_triggered);
    connect(action13,&QAction::triggered,this,&on_actionCenter_triggered);
    connect(action14,&QAction::triggered,this,&on_actionRight_triggered);    
    connect(action15,&QAction::triggered,this,&on_actionTextUnderLine_triggered);
    connect(action16,&QAction::triggered,this,&on_actioncolor_triggered);
    connect(action17,&QAction::triggered,this,&on_actionfont_triggered);
    connect(action18,&QAction::triggered,this,&on_about);
    connect(action19,&QAction::triggered,this,&on_actionpdf_triggered);
    connect(action20,&QAction::triggered,this,&textRemoveFormat);
    connect(action21,&QAction::triggered,this,&textStrikeout);
    connect(action22,&QAction::triggered,this,&textLink);
    connect(action23,&QAction::triggered,this,&textBgColor);
    connect(action24,&QAction::triggered,this,&listBullet);   
    connect(action25,&QAction::triggered,this,&listOrdered);
    connect(action26,&QAction::triggered,this,&increaseIndentation);
    connect(action27,&QAction::triggered,this,&decreaseIndentation);
    connect(action28,&QAction::triggered,this,&insertImage);
    connect(action29,&QAction::triggered,this,&splitPage);
    connect(action30,&QAction::triggered,this,&splitPragraph);
    connect(action31,&QAction::triggered,this,&on_actionhtml_triggered);
    connect(action32,&QAction::triggered,this,&on_actionrtf_triggered);
    connect(action33,&QAction::triggered,this,&on_actionmarkdown_triggered);
    connect(action34,&QAction::triggered,this,&showDialog);
    connect(action35,&QAction::triggered,this,&start_coding);
    connect(action36,&QAction::triggered,this,&back_normal);
    connect(action37,&QAction::triggered,this,&change_editor_mood); 
    connect(action38,&QAction::triggered,this,&on_actioncomplie_triggered);
    connect(action39,&QAction::triggered,this,&on_actionrun_triggered);
    connect(action40,&QAction::triggered,this,&on_actioncomplieANDrun_triggered);        
    connect(fontsize,&QComboBox::currentTextChanged,this,&textSize);
    connect(decodeButton, &QPushButton::clicked, this, &onDecodeButtonClicked);
}
Editor::~Editor()
{
}
void Editor::on_actionexit_triggered()
{
    close();
}
QString Editor::showFileDialog(QFileDialog::AcceptMode mode)
{
    //这个函数可以实现对于文件的打开以及保存
    QString ret = "";
    QFileDialog fd(this);
    QStringList filters;

    filters << "All Files (*)" <<"TXT Files (*.txt)" << "C Files (*.c)" << "C++ Files (*.cpp)";

    fd.setWindowTitle("文件");//对话框标题
    fd.setAcceptMode(mode);
    fd.selectFile("untitled.txt");
    fd.setNameFilters(filters);

    if( mode == QFileDialog::AcceptOpen )//是打开文件还是保存文件
    {
        fd.setFileMode(QFileDialog::ExistingFile);//设置可选单个已存在的文件
    }

    if( fd.exec() == QFileDialog::Accepted )
    {
        ret = fd.selectedFiles()[0];//函数返回装有选中的文件的绝对路径的链表
    }

    return ret;
}
/*******************对文件进行操作*********************/
//打开文件！！
void Editor::setCurrentFileName(const QString &fileName)
{
    m_fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowModified(false);
}


void Editor::on_actionopenfile_triggered() {
    path = showFileDialog(QFileDialog::AcceptOpen);
    setCurrentFileName(path);

    if (path.isEmpty()) {
        return;
    }

    QFile file(path);

    if (file.open(QIODevice::ReadOnly)) 
    {
        // 读取文件内容
        QByteArray fileData = file.readAll();
        QTextCodec::ConverterState state;
        // 检测文件编码
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString decodedText = codec->toUnicode(fileData.constData(),fileData.size(),&state);

        // 如果检测到不是 UTF-8 编码，则使用 GB2312 进行解码
        if (state.invalidChars>0) {
            codec->codecForName("GB2312");
            decodedText = codec->toUnicode(fileData.constData(),fileData.size(),&state);

            // 如果还不是，则尝试使用 ANSI 编码进行解码
            if (state.invalidChars>0) {
                codec->codecForName("GBK");
                decodedText = codec->toUnicode(fileData.constData(),fileData.size(),&state);
                if (state.invalidChars>0)
                {
                    QTextDecoder ansiDecoder(QTextCodec::codecForLocale()); // 使用ANSI
                    decodedText = ansiDecoder.toUnicode(fileData);                    
                }

            }
        }

        // 在 QTextEdit 中显示文本
        textEdit->setPlainText(decodedText);

        file.close();
        setWindowTitle("TMC - [ " + path + " ]");
    } else {
        // 文件打开失败
        // showErrorMessage(QString("Open file error! \n\n") + "\"" + path + "\"");
    }
}
// void Editor ::on_actionopenfile_triggered()
// {

//     QString path = showFileDialog(QFileDialog::AcceptOpen);
//     setCurrentFileName(path);
//     if( path != "" )
//     {
//         QFile file(path);

//         if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
//         {
//             textEdit->setPlainText(QString(file.readAll()));//读取文件的所有数据并导入到编辑组件
//             file.close();
//             setWindowTitle("TMC - [ " + path + " ]");
//         }
//         else
//         {
//             //showErrorMessage(QString("Open file error! \n\n") + "\"" + path + "\"");//自定义的一个错误提示对话框
//         }
//     }

// }
//创建文件
void Editor::on_actionne_triggered()
{
    QMessageBox::StandardButton ok=QMessageBox::warning(this,tr("Warning"),
    tr("创建新文件？"),
    QMessageBox::Yes | QMessageBox::Default,
    QMessageBox::No);//通过QMessagebox里面的东西来

    m_fileName.clear();
    textEdit->setText(QString());
    if( m_fileName == ""&& ok==QMessageBox::StandardButton::Yes)
        m_fileName = showFileDialog(QFileDialog::AcceptSave);

}

//保存文件
QString Editor::saveCurrentData(QString path)
{
    QString ret = path;

    if( ret == "" )
        ret = showFileDialog(QFileDialog::AcceptSave);
    if( ret != "" )
    {
        QFile file(ret);
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            setWindowTitle("NotePad - [ " + ret + " ]");
        }
        else
        {
            ret = "";
        }
    }
    return ret;
}

void Editor::on_ServeFile_triggered()
{
    path = saveCurrentData(m_fileName);

    if( path != "" )
    {
        m_fileName = path;
    }

}
/*******************对文件进行操作*********************/
/********************************撤销与恢复****************************/
void Editor::on_actionundo_triggered()
{
    textEdit->undo();
}

void Editor::on_actionredo_triggered()
{
    textEdit->redo();
}

/********************************撤销与恢复****************************/
/************剪切******************/
void Editor::on_actioncut_triggered()
{
    textEdit->cut();
}

void Editor::on_actioncopy_triggered()
{
    textEdit->copy();
}
void Editor::on_actionpatse_triggered()
{
    textEdit->paste();
}
/************剪切******************/
/************粗体，斜体，下划线*************************/

//  设置光标的选区，使格式作用于选区内的字符
void Editor::mergeFormat(QTextCharFormat fmt)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection()) {
    cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(fmt);
    textEdit->mergeCurrentCharFormat(fmt);
    textEdit->setFocus(Qt::TabFocusReason);
}

//加粗
void Editor::on_actionTextBold_triggered()
{
    static bool boldcheck=true;
    QTextCharFormat fmt;
    fmt.setFontWeight(boldcheck ? QFont::Bold : QFont::Normal);
    mergeFormat(fmt);
    boldcheck = !boldcheck;
}
//倾斜
void Editor::on_actionTextItalic_triggered()
{
    static bool Italiccheck=true;
    QTextCharFormat fmt;
    fmt.setFontItalic(Italiccheck ? true : false);
    mergeFormat(fmt);
    Italiccheck = !Italiccheck;
}
//下划线
void Editor::on_actionTextUnderLine_triggered()
{
    static bool UnderLinecheck=true;
    QTextCharFormat fmt;
    fmt.setFontUnderline(UnderLinecheck ? true : false);
    mergeFormat(fmt);
    UnderLinecheck = !UnderLinecheck;
}

void Editor::textStrikeout()
{
    static bool FontStrikeOut=true;
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(FontStrikeOut ? true : false);
    mergeFormat(fmt);
    FontStrikeOut = !FontStrikeOut;
}

/************粗体，斜体，下划线*************************/
/*******************对齐********************/
//左对齐
void Editor::on_actionLift_triggered()
{
    textEdit->setAlignment(Qt::AlignLeft);
}
//居中对齐
void Editor::on_actionCenter_triggered()
{
    textEdit->setAlignment(Qt::AlignCenter);
}
//右对齐
void Editor::on_actionRight_triggered()
{
    textEdit->setAlignment(Qt::AlignRight);
}

/*******************对齐********************/
/********************颜色，字体******************************/
void Editor::on_actioncolor_triggered()
{
    QColor c = QColorDialog::getColor(color,this,"颜色选择框");
    if(c.isValid()){
        color = c;

        // 设置文本框的文本颜色
        // 1. 从光标开始新输入的文本颜色被设置
        // 2. 鼠标选中的文本颜色设置
        textEdit->setTextColor(c);
    }
}
void Editor::on_actionfont_triggered()
{
    bool ok; // 用户字体对话框保存是否选择了字体的结构

    // 第一个参数是判断用户是否选择了字体，第二个是字体对话框的初始值
    QFont f = QFontDialog::getFont(&ok,font,this,"选择文本框要设置的字体");//基础的用户字体对话框

    if(ok){
        font = f;

        // 1. 从当前光标开始
        // 2. 鼠标选中的文本的字体
        textEdit->setCurrentFont(f);
    }

}

void Editor::on_actionpdf_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "导出文件", "", "pdf文件(*.pdf);;");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    textEdit->document()->print(&printer);
}

void Editor::textRemoveFormat()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(QFont::Normal);
    fmt.setFontUnderline(false);
    fmt.setFontStrikeOut(false);
    fmt.setFontItalic(false);
    fmt.setFontPointSize(12);
    fmt.clearBackground();

    mergeFormat(fmt);
}

void Editor::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormat(fmt);
    }
}

void Editor::textLink()
{
    bool unlink = false;
    QTextCharFormat fmt;
    if (!unlink)
    {
        QString url = textEdit->currentCharFormat().anchorHref();
        bool ok;
        QString newUrl = QInputDialog::getText(this, tr("Create a link"),
                                               tr("Link URL:"), QLineEdit::Normal,
                                               url,
                                               &ok);
        if (ok)
        {
            fmt.setAnchor(true);
            fmt.setAnchorHref(newUrl);
            fmt.setForeground(QApplication::palette().color(QPalette::Link));
            fmt.setFontUnderline(true);
        } else
        {
            unlink = true;
        }
    } else
    {
        unlink = true;
    }
    if (unlink)
    {
        fmt.setAnchor(false);
        fmt.setForeground(QApplication::palette().color(QPalette::Text));
        fmt.setFontUnderline(false);
    }
    mergeFormat(fmt);
}


void Editor::textBgColor()
{
    QColor col = QColorDialog::getColor(textEdit->textBackgroundColor(), this);
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    QTextCharFormat fmt = cursor.charFormat();
    if (col.isValid())
    {
        fmt.setBackground(col);
    } else
    {
        fmt.clearBackground();
    }
    cursor.setCharFormat(fmt);
    textEdit->setCurrentCharFormat(fmt);

}

void Editor::listBullet()
{
    static bool check=true;
    list(check, QTextListFormat::ListDisc);
    check = !check;
}

void Editor::listOrdered()
{
    static bool check=true;
    list(check, QTextListFormat::ListDecimal);
    check = !check;
}

void Editor::list(bool checked, QTextListFormat::Style style)
{
    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    if (!checked)
    {
        QTextBlockFormat obfmt = cursor.blockFormat();
        QTextBlockFormat bfmt;
        bfmt.setIndent(obfmt.indent());
        cursor.setBlockFormat(bfmt);
    } else
    {
        QTextListFormat listFmt;
        if (cursor.currentList())
        {
            listFmt = cursor.currentList()->format();
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }
    cursor.endEditBlock();
}

void Editor::increaseIndentation()
{
    indent(+1);
}

void Editor::decreaseIndentation()
{
    indent(-1);
}

void Editor::indent(int delta)
{
    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    QTextBlockFormat bfmt = cursor.blockFormat();
    int ind = bfmt.indent();
    if (ind + delta >= 0)
    {
        bfmt.setIndent(ind + delta);
    }
    cursor.setBlockFormat(bfmt);
    cursor.endEditBlock();
}

void Editor::insertImage()
{
    QSettings s;
    QString attdir = s.value("general/filedialog-path").toString();
    QString file = QFileDialog::getOpenFileName(this,
                                                tr("Select an image"),
                                                attdir,
                                                tr("image (*.jpg *.gif *.png *.bmp);; JPEG (*.jpg);; GIF (*.gif);; PNG (*.png);; BMP (*.bmp);; All (*)"));
    
    QImage image = QImageReader(file).read();
    QString format = QFileInfo(file).suffix().toUpper().toLocal8Bit().data();
    QByteArray bytes;
    QBuffer buffer(&bytes);

    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, format.toLocal8Bit().data());
    buffer.close();
    QByteArray base64 = bytes.toBase64();
    QByteArray base64l;
    for (int i = 0; i < base64.size(); i++)
    {
        base64l.append(base64[i]);
        if (i % 80 == 0)
        {
            base64l.append("\n");
        }
    }

    QTextCursor cursor = textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth(image.width());
    imageFormat.setHeight(image.height());
    imageFormat.setName(QString("data:image/%1;base64,%2")
                            .arg(QString("%1.%2").arg(rand()).arg(format))
                            .arg(base64l.data())
    );
    cursor.insertImage(imageFormat);
}

void Editor::on_actionrtf_triggered()
{
    //保存代码
    QFileDialog fileDialog(this);
    QFile myFile(fileDialog.getSaveFileName(this, tr("导出文件"),".",tr("富文本(*.rtf);;")));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (myFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&myFile);
        stream<<textEdit->toHtml().toUtf8();
    }
}

void Editor::on_actionmarkdown_triggered()
{
    //保存代码
    QFileDialog fileDialog(this);
    QFile myFile(fileDialog.getSaveFileName(this, tr("导出文件"),".",tr("MarkDown(*.md);;")));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (myFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&myFile);
        stream<<textEdit->toMarkdown();
    }
}


void Editor::on_actionhtml_triggered() {
    // 弹出文件对话框，获取用户选择的文件路径
    QFileDialog fileDialog(this);
    QString file = fileDialog.getSaveFileName(this, "导出文件", "", "HTML文件(*.html);;");
    
    // 如果用户取消选择文件，则返回
    if (file.isEmpty()) {
        qDebug() << "未选择文件";
        return;
    }

    // 获取 HTML 内容并保存到用户指定的文件
    QString htmlContent = textEdit->toHtml();
    QFile outputFile(file);

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream textStream(&outputFile);
        textStream << htmlContent;
        outputFile.close();
        qDebug() << "HTML 文件已导出至" << file;
    } else {
        qDebug() << "无法创建/写入 HTML 文件";
    }
}


void saveHtmlWithImages(const QTextEdit *textEdit, const QString &filename) {
    // 获取文本编辑器的文档
    QTextDocument *document = textEdit->document();

    // 获取HTML格式的文本
    QString html = document->toHtml();

    // 创建文件
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        // 写入HTML内容到文件
        stream << html;

        file.close();
    }
}

void Editor::applySettings(double lineSpacing, int margin) 
{
    // 获取文档
    QTextDocument *document = textEdit->document();

    // 设置行间距
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(lineSpacing, QTextBlockFormat::LineDistanceHeight);
    QTextCursor cursor(document);
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);

    //设置页边距
    QSizeF pageSize = document->pageSize();
    pageSize.setWidth(pageSize.width() - 2 * margin);
    pageSize.setHeight(pageSize.height() - 2 * margin);
    document->setPageSize(pageSize);
    document->setDocumentMargin(margin);
}

void Editor::on_about()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://doc.qt.io/")));
}

void Editor::start_coding()
{
    toolBar->setHidden(true);
    highlighter->setHighlightingEnabled(true);
    highlighter->setDocument(textEdit->document());
    statusLabel->setText("Coding Mode");
    mood = 1;
    action37->setIcon(QIcon(":/Editor/sun.ico"));
    setStyleSheet("background-color: #2E2E2E; color: #FFFFFF;");  
    if(statusLabel->text()=="Normal Edit")       
        textEdit->setStyleSheet("QTextEdit { border: 0px; }"
                            "QTextEdit::handle { width: 0px; height: 0px; }");
    else
        textEdit->setStyleSheet("QTextEdit { background-color: #2E2E2E; color: #8CDCFE; }"
                                "QTextEdit { border: 0px; }"
                                "QTextEdit::handle { width: 0px; height: 0px; }");      
    toolBar->setStyleSheet("QToolBar { background-color: #404040;}"
                            "QToolBar { border: 0px; }"
                            "QToolBar::handle { width: 0px; height: 0px; }"); 
    status->setStyleSheet("QStatusBar { background-color: #404040;}"
                            "QStatusBar { border: 0px; }"
                            "QStatusBar::handle { width: 0px; height: 0px; }"); 
    decodeButton->setStyleSheet("background-color: #404040;""border: none;");
    statusLabel->setStyleSheet("background-color: #404040;");
    status->addPermanentWidget(statusLabel);
}

void Editor::on_actioncomplie_triggered() 
{
    if(path.isEmpty())
    {
        // 如果没有路径则需要保存一下才能运行
        this->on_ServeFile_triggered();
    }

    QString demo = path;
    demo.replace(".c", "");

    // 编译命令
    QString compileCmd = QString("g++ \"%1\" -o \"%2\"").arg(path).arg(demo);

    // 创建 QProcess 对象
    QProcess process;

    // 启动编译进程
    process.start(compileCmd);
    process.waitForFinished();

    // 检查编译结果
    if (process.exitCode() != 0) {
        // 编译失败
        QMessageBox::critical(this, "Compile Error", "Compilation failed. Please check the code and compiler settings.");
        return;
    }
    else
    {
        QMessageBox::information(this, "Notice","Compile Succeed");
    }
}

void Editor::on_actionrun_triggered() {
    QString dest = path;
    dest.replace(".cpp", "");
    dest.replace(".c", "");
    QString executeCmd = QString("%1 && pause").arg(dest);
    system(executeCmd.toStdString().data());
}

void Editor::on_actioncomplieANDrun_triggered()
{
    if(path.isEmpty())
    {
        // 如果没有路径则需要保存一下才能运行
        this->on_ServeFile_triggered();
    }

    QString demo = path;
    demo.replace(".cpp", "");
    demo.replace(".c", "");

    // 编译命令
    QString compileCmd = QString("g++ \"%1\" -o \"%2\"").arg(path).arg(demo);

    QString cmd = QString("g++ %1 -o %2").arg(path).arg(demo);

    // system执行成返回0
    int ret = system(cmd.toStdString().data());
    if(ret != 0)
    {
        // cmd /k 停留在终端
        cmd = QString("cmd /k g++ %1 -o %2").arg(path).arg(demo);
        system(cmd.toStdString().data());
        return;
    }
    // 编译成功，执行目标文件
    QString executeCmd = QString("%1 && pause").arg(demo);
    system(executeCmd.toStdString().data());

}
void Editor::back_normal()
{
    toolBar->setHidden(false);
    highlighter->setHighlightingEnabled(false);
    highlighter->setDocument(textEdit->document());
    statusLabel->setText("Normal Edit");
    mood =  0;
    action37->setIcon(QIcon(":/Editor/moon.ico"));
    setStyleSheet("background-color: #F0F0F0; color: #000000;"); 
    if(statusLabel->text()=="Normal Edit")       
        textEdit->setStyleSheet("QTextEdit { border: 0px; }"
                            "QTextEdit::handle { width: 0px; height: 0px; }");
    else
        textEdit->setStyleSheet("QTextEdit { background-color: #F0F0F0; color: #8CDCFE; }"
                                "QTextEdit { border: 0px; }"
                                "QTextEdit::handle { width: 0px; height: 0px; }");
    toolBar->setStyleSheet("QToolBar { background-color: #FFFFFF;}"
                            "QToolBar { border: 0px; }"
                            "QToolBar::handle { width: 0px; height: 0px; }");
    status->setStyleSheet("QStatusBar { background-color: #FFFFFF;}"
                            "QStatusBar { border: 0px; }"
                            "QStatusBar::handle { width: 0px; height: 0px; }"); 
    decodeButton->setStyleSheet("background-color: #FFFFFF;""border: none;");
    statusLabel->setStyleSheet("background-color: #FFFFFF;");   
    status->addPermanentWidget(statusLabel);
}


void Editor::change_editor_mood()
{
    if(!mood)
    {
        action37->setIcon(QIcon(":/Editor/sun.ico"));
        setStyleSheet("background-color: #2E2E2E; color: #FFFFFF;");  
        if(statusLabel->text()=="Normal Edit")       
            textEdit->setStyleSheet("QTextEdit { border: 0px; }"
                                "QTextEdit::handle { width: 0px; height: 0px; }");
        else
            textEdit->setStyleSheet("QTextEdit { background-color: #2E2E2E; color: #8CDCFE; }"
                                    "QTextEdit { border: 0px; }"
                                    "QTextEdit::handle { width: 0px; height: 0px; }");      
        toolBar->setStyleSheet("QToolBar { background-color: #404040;}"
                                "QToolBar { border: 0px; }"
                                "QToolBar::handle { width: 0px; height: 0px; }"); 
        decodeButton->setStyleSheet("background-color: #404040;""border: none;");  
        statusLabel->setStyleSheet("background-color: #404040;");                             
        status->setStyleSheet("QStatusBar { background-color: #404040;}"
                                "QStatusBar { border: 0px; }"
                                "QStatusBar::handle { width: 0px; height: 0px; }"); 

    }   
    else 
    {
        action37->setIcon(QIcon(":/Editor/moon.ico"));
        setStyleSheet("background-color: #F0F0F0; color: #000000;"); 
        if(statusLabel->text()=="Normal Edit")       
            textEdit->setStyleSheet("QTextEdit { border: 0px; }"
                                "QTextEdit::handle { width: 0px; height: 0px; }");
        else
            textEdit->setStyleSheet("QTextEdit { background-color: #F0F0F0; color: #8CDCFE; }"
                                    "QTextEdit { border: 0px; }"
                                    "QTextEdit::handle { width: 0px; height: 0px; }");
        toolBar->setStyleSheet("QToolBar { background-color: #FFFFFF;}"
                                "QToolBar { border: 0px; }"
                                "QToolBar::handle { width: 0px; height: 0px; }");
        decodeButton->setStyleSheet("background-color: #FFFFFF;""border: none;");
        statusLabel->setStyleSheet("background-color: #FFFFFF;");   
        status->setStyleSheet("QStatusBar { background-color: #FFFFFF;}"
                                "QStatusBar { border: 0px; }"
                                "QStatusBar::handle { width: 0px; height: 0px; }"); 


    }
    mood = !mood;
}

bool Editor::parseCommandLine() {
        // 创建命令行解析器
        QCommandLineParser parser;
        parser.setApplicationDescription("tmc");
        parser.addHelpOption();
        parser.addVersionOption();

        // 添加自定义的命令行选项
        QCommandLineOption fileOption(QStringList() << "f" << "file", "Open specified file.", "file");
        parser.addOption(fileOption);

        // 解析命令行
        parser.process(QCoreApplication::arguments());

        // 处理命令行选项
        if (parser.isSet(fileOption)) 
        {
            QString fileName = parser.value(fileOption);
            QString relativePath = fileName;

            // 获取当前应用程序的工作目录
            QString currentPath = QDir::currentPath();
            path = QDir::cleanPath(QDir(currentPath).absoluteFilePath(relativePath));
            
            // 打开指定文件            
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) 
            {
                // 读取文件内容
                QByteArray fileData = file.readAll();
                QTextCodec::ConverterState state;
                // 检测文件编码
                QTextCodec *codec = QTextCodec::codecForName("UTF-8");
                QString decodedText = codec->toUnicode(fileData.constData(),fileData.size(),&state);

                // 如果检测到不是 UTF-8 编码，则使用 GB2312 进行解码
                if (state.invalidChars>0) {
                    codec->codecForName("GB2312");
                    decodedText = codec->toUnicode(fileData.constData(),fileData.size(),&state);

                    // 如果还不是，则尝试使用 ANSI 编码进行解码
                    if (state.invalidChars>0) {
                        codec->codecForName("GBK");
                        decodedText = codec->toUnicode(fileData.constData(),fileData.size(),&state);
                        if (state.invalidChars>0)
                        {
                            QTextDecoder ansiDecoder(QTextCodec::codecForLocale()); // 使用ANSI
                            decodedText = ansiDecoder.toUnicode(fileData);                    
                        }

                    }
                }

                // 在 QTextEdit 中显示文本
                textEdit->setPlainText(decodedText);

                file.close();
                setWindowTitle("TMC - [ " + path + " ]");
            } 
            else 
            {
                // 文件打开失败
                // showErrorMessage(QString("Open file error! \n\n") + "\"" + path + "\"");
            }
        }
        return false;
    }

void Editor::onDecodeButtonClicked() 
{
    // 弹出对话框，包含一个 QComboBox 供用户选择编码方式
    QDialog dialog(this);
    dialog.setWindowTitle("Choose Encoding");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QComboBox *encodingComboBox = new QComboBox(&dialog);
    
    // foreach (const QByteArray &codecName, QTextCodec::availableCodecs()) {
    //     encodingComboBox->addItem(QString(codecName));
    // }
    encodingComboBox->addItems({"UTF-8", "GB2312","GBK", "ISO 8859-1" , "UTF-16", "Windows-1252", "ASCII"});
    encodingComboBox->setToolTip("选择解码方式");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    layout->addWidget(encodingComboBox);
    layout->addWidget(buttonBox);

    // 如果用户点击了确定按钮
    if (dialog.exec() == QDialog::Accepted) {
        // 获取用户选择的解码方式
        QString encoding = encodingComboBox->currentText();

        decodeButton->setText(encoding);
        // 根据选择的解码方式设置相应的编码器
        QTextCodec *codec = QTextCodec::codecForName(encoding.toUtf8());

        if (!path.isEmpty()) 
        {
            QFile file(path);
            if (file.open(QIODevice::ReadOnly)) {
                QByteArray fileData = file.readAll();
                QString decodedText = codec->toUnicode(fileData);
                textEdit->setPlainText(decodedText);
                file.close();
            } else {
                QMessageBox::information(this, "tips", "Open a file");
            }
        }
        else
            QMessageBox::information(this, "tips", "path empty");
    }
}

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(keyword);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\bsizeof\\b"),QStringLiteral("\\bextern\\b"),QStringLiteral("\\btrue\\b"),
        QStringLiteral("\\bfalse\\b")
    };
    for (const QString &pattern : keywordPatterns) 
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
//! [0] //! [1]
    }
//! [1]

//! [2]Qt类名
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(classname);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);
//! [2]

//! [3]单行注释
    singleLineCommentFormat.setForeground(comment);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(comment);
//! [3]

//! [4]字符串
    quotationFormat.setForeground(string);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//! [4]

//! [5]函数名
    functionFormat.setFontItalic(false);
    functionFormat.setForeground(function);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);
//! [5]

//! [6]多行注释
    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
//! [6]

//! [7]宏定义和括号以及其他关键词
    mecroFormat.setFontItalic(false);
    mecroFormat.setForeground(red_new);
    rule.pattern = QRegularExpression(QStringLiteral(R"(\b#(\w+)\b)"));
    rule.format = mecroFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegularExpression(QStringLiteral(R"(#(\w+)\b)"));
    rule.format = mecroFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegularExpression(QStringLiteral(R"([{}[\]()])"));
    rule.format = mecroFormat;
    highlightingRules.append(rule);

    const QString rest_keyPatterns[] = {
        QStringLiteral("\\bfor\\b"), QStringLiteral("\\bwhile\\b"), QStringLiteral("\\bnew\\b"),
        QStringLiteral("\\bif\\b"), QStringLiteral("\\belse\\b"),QStringLiteral("\\bbreak\\b"), 
        QStringLiteral("\\bdefaut\\b"), QStringLiteral("\\bcontinue\\b"),QStringLiteral("\\breturn\\b"),
        QStringLiteral("\\bswitch\\b"),QStringLiteral("\\bcase\\b"),QStringLiteral("\\bdo\\b"),
        QStringLiteral("\\bcontinue\\b"),QStringLiteral("\\delete\\b")
    };

    for (const QString &pattern : rest_keyPatterns) 
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = mecroFormat;
        highlightingRules.append(rule);
    }
}



void Highlighter::highlightBlock(const QString &text)
{
    if(highlightEnabled == false)   //如果为false直接返回
        return;
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
//! [7] //! [8]
    setCurrentBlockState(0);
//! [8]

//! [9]
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

//! [9] //! [10]
    while (startIndex >= 0) {
//! [10] //! [11]
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

QTextEditHighlighter::QTextEditHighlighter(QWidget *parent) :
    QTextEdit(parent)
{
    // Line numbers
    lineNumberArea = new LineNumberArea(this);
    ///
    // connect(this->document(), SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this->document(), &QTextDocument::blockCountChanged, this, &updateLineNumberAreaWidth);
    // connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateLineNumberArea/*_2*/(int)));
    connect(this->verticalScrollBar(), &QScrollBar::valueChanged, this, &updateLineNumberArea/*_2*/);
    connect(this, &QTextEdit::textChanged, this, &updateLineNumberArea);
    connect(this, &QTextEdit::cursorPositionChanged, this, &updateLineNumberArea);
    ///
    updateLineNumberAreaWidth(0);
}

int QTextEditHighlighter::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, this->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 13 +  fontMetrics().horizontalAdvance(QLatin1Char('9')) * (digits);

    return space;
}

void QTextEditHighlighter::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QTextEditHighlighter::updateLineNumberArea()
{
    /*
     * When the signal is emitted, the sliderPosition has been adjusted according to the action,
     * but the value has not yet been propagated (meaning the valueChanged() signal was not yet emitted),
     * and the visual display has not been updated. In slots connected to this signal you can thus safely
     * adjust any action by calling setSliderPosition() yourself, based on both the action and the
     * slider's value.
     */
    // Make sure the sliderPosition triggers one last time the valueChanged() signal with the actual value !!!!
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    // Since "QTextEdit" does not have an "updateRequest(...)" signal, we chose
    // to grab the imformations from "sliderPosition()" and "contentsRect()".
    // See the necessary connections used (Class constructor implementation part).

    QRect rect =  this->contentsRect();
    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    updateLineNumberAreaWidth(0);
    //----------
    int dy = this->verticalScrollBar()->sliderPosition();
    if (dy > -1) {
        lineNumberArea->scroll(0, dy);
    }

    // Addjust slider to alway see the number of the currently being edited line...
    int first_block_id = getFirstVisibleBlockId();
    if (first_block_id == 0 || this->textCursor().block().blockNumber() == first_block_id-1)
        this->verticalScrollBar()->setSliderPosition(dy-this->document()->documentMargin());

//    // Snap to first line (TODO...)
//    if (first_block_id > 0)
//    {
//        int slider_pos = this->verticalScrollBar()->sliderPosition();
//        int prev_block_height = (int) this->document()->documentLayout()->blockBoundingRect(this->document()->findBlockByNumber(first_block_id-1)).height();
//        if (dy <= this->document()->documentMargin() + prev_block_height)
//            this->verticalScrollBar()->setSliderPosition(slider_pos - (this->document()->documentMargin() + prev_block_height));
//    }

}


void QTextEditHighlighter::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    QRect cr = this->contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


int QTextEditHighlighter::getFirstVisibleBlockId()
{
    // Detect the first block for which bounding rect - once translated 
    // in absolute coordinated - is contained by the editor's text area

    // Costly way of doing but since "blockBoundingGeometry(...)" doesn't 
    // exists for "QTextEdit"...

    QTextCursor curs = QTextCursor(this->document());
    curs.movePosition(QTextCursor::Start);
    for(int i=0; i < this->document()->blockCount(); ++i)
    {
        QTextBlock block = curs.block();

        QRect r1 = this->viewport()->geometry();
        QRect r2 = this->document()->documentLayout()->blockBoundingRect(block).translated(
                    this->viewport()->geometry().x(), this->viewport()->geometry().y() - (
                        this->verticalScrollBar()->sliderPosition()
                        ) ).toRect();

        if (r1.contains(r2, true)) { return i; }

        curs.movePosition(QTextCursor::NextBlock);
    }

    return 0;
}

void QTextEditHighlighter::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::darkGray);
    int blockNumber = this->getFirstVisibleBlockId();

    QTextBlock block = this->document()->findBlockByNumber(blockNumber);
    QTextBlock prev_block = (blockNumber > 0) ? this->document()->findBlockByNumber(blockNumber-1) : block;
    int translate_y = (blockNumber > 0) ? -this->verticalScrollBar()->sliderPosition() : 0;

    int top = this->viewport()->geometry().top();

    // Adjust text position according to the previous "non entirely visible" block 
    // if applicable. Also takes in consideration the document's margin offset.
    int additional_margin;
    if (blockNumber == 0)
        // Simply adjust to document's margin
        additional_margin = (int) this->document()->documentMargin() -1 - this->verticalScrollBar()->sliderPosition();
    else
        // Getting the height of the visible part of the previous "non entirely visible" block
        additional_margin = (int) this->document()->documentLayout()->blockBoundingRect(prev_block)
                .translated(0, translate_y).intersected(this->viewport()->geometry()).height();

    // Shift the starting point
    top += additional_margin;

    int bottom = top + (int) this->document()->documentLayout()->blockBoundingRect(block).height();

    QColor col_1(255, 255, 255);      // Current line (custom color)
    QColor col_0(120, 120, 120);    // Other lines  (custom darkgrey)

    // Draw the numbers (displaying the current line number in green)
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(120, 120, 120));
            painter.setPen((this->textCursor().blockNumber() == blockNumber) ? col_1 : Qt::lightGray);
            painter.drawText(-5, top,
                             lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) this->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }
}