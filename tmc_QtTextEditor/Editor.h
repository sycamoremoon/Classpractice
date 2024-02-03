#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtCore5Compat/QtCore5Compat>
class QTextEditHighlighter : public QTextEdit
{
    public:

        explicit QTextEditHighlighter(QWidget *parent = 0);

        int getFirstVisibleBlockId();
        void lineNumberAreaPaintEvent(QPaintEvent *event);
        int lineNumberAreaWidth();


    signals:


    public slots:

        void resizeEvent(QResizeEvent *e);

        void updateLineNumberAreaWidth(int newBlockCount);

        void updateLineNumberArea();

    private:

        QWidget *lineNumberArea;

};

class LineNumberArea : public QWidget
{
    public:
        LineNumberArea(QTextEdit *editor) : QWidget(editor) 
            {codeEditor = editor;}

        QSize sizeHint() const
        {return QSize(((QTextEditHighlighter *)codeEditor)->lineNumberAreaWidth(), 0);}

    protected:
        void paintEvent(QPaintEvent *event)
        {((QTextEditHighlighter *)codeEditor)->lineNumberAreaPaintEvent(event);}

    private:
        QTextEdit *codeEditor;
};

class MyDialog : public QDialog
{
	public:
		MyDialog(QWidget *parent = 0); //构造函数
        QDoubleSpinBox *lineSpacingSpinBox;
        QSpinBox *marginSpinBox;
	private:
		void applyButtonClicked(); //OK按钮点击时的处理函数

};

class Highlighter : public QSyntaxHighlighter
{

    public:
        Highlighter(QTextDocument *parent = nullptr);
        void setHighlightingEnabled(bool enable)
        {highlightEnabled = enable;}

    protected:
        void highlightBlock(const QString &text) override;

    private:
        struct HighlightingRule
        {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QList<HighlightingRule> highlightingRules;

        QRegularExpression commentStartExpression;
        QRegularExpression commentEndExpression;

        QTextCharFormat keywordFormat;
        QTextCharFormat classFormat;
        QTextCharFormat singleLineCommentFormat;
        QTextCharFormat multiLineCommentFormat;
        QTextCharFormat quotationFormat;
        QTextCharFormat functionFormat;
        QTextCharFormat mecroFormat;
    
        bool highlightEnabled = false;
        QColor variable = QColor(140,220,254);
        QColor classname = QColor(78,201,176);
        QColor keyword = QColor(75,156,214);
        QColor red_new = QColor(218,112,214);
        QColor string = QColor(206,131,74);
        QColor comment = QColor(82,153,85);
        QColor function = QColor(220,185,74);        
};

class Editor:public QMainWindow//定义一个Editor类，继承自QEditor窗口类
{

	public:
		Editor(QWidget *parent = nullptr); //构造函数，参数是父窗体指针，默认是0，即没有父窗口
        ~Editor();

        QString saveCurrentData(QString path);
        void setCurrentFileName(const QString &fileName);
        QString showFileDialog(QFileDialog::AcceptMode mode);
        void mergeFormat(QTextCharFormat fmt);
        bool mood =0;

        // 命令行参数
        bool parseCommandLine();
        QString path;

	private:
        QString m_fileName;
        QFont font;
        QColor color;
        QComboBox *fontsize;
        QComboBox *paragraph;
        enum ParagraphItems
        {
            ParagraphStandard = 0,
            ParagraphSansSerif,
            ParagraphSystem,
            ParagraphHelvetica,
            ParagraphCourier,
            ParagraphMonospace
        };
        //创建菜单
        QMenu *menu1 = new QMenu("文件",this);//文件
        QMenu *menu2 = new QMenu("编辑",this);//编辑
        QMenu *menu3 = new QMenu("Coding",this);//coding
        QMenu *menu4 = new QMenu("构建",this);//构建
        QMenu *menu5 = new QMenu("调试",this);//调试
        QMenu *menu6 = new QMenu("主题",this);//工具
        QMenu *menu7 = new QMenu("帮助",this);//帮助
        QMenu *menu9 = new QMenu("导出为其他格式",this);
        QMenuBar *menuBar = new QMenuBar(this);

        //创建工具栏
        QToolBar *toolBar = new QToolBar(this);
        //创建工具项
        QAction *action1 = new QAction(QIcon(":/Editor/add-page.ico"),"新建文件或项目",this);//有新建文件
        QAction *action2 = new QAction(QIcon(":/Editor/open-page.ico"),"打开文件或项目",this);//有打开文件
        QAction *action3 = new QAction(QIcon(":/Editor/cut.ico"),"剪切",this);//剪切
        QAction *action4 = new QAction(QIcon(":/Editor/copy.ico"),"复制",this);//复制
        QAction *action5 = new QAction(QIcon(":/Editor/paste.ico"),"粘贴",this);//粘贴
        QAction *action6 = new QAction(QIcon(":/Editor/close.ico"),"退出",this);//退出
        QAction *action7 = new QAction(QIcon(":/Editor/save.ico"),"保存文件或项目",this);//保存
        QAction *action8 = new QAction(QIcon(":/Editor/undo.ico"),"撤回",this);//撤回
        QAction *action9 = new QAction(QIcon(":/Editor/redo.ico"),"重做",this);//重做
        QAction *action10 = new QAction(QIcon(":/Editor/bold.ico"),"粗体",this);//粗体
        QAction *action11 = new QAction(QIcon(":/Editor/italic.ico"),"斜体",this);//斜体
        QAction *action12 = new QAction(QIcon(":/Editor/align_left.ico"),"左对齐",this);//左对齐
        QAction *action13 = new QAction(QIcon(":/Editor/align_center.ico"),"居中对齐",this);//居中对齐
        QAction *action14 = new QAction(QIcon(":/Editor/align_right.ico"),"右对齐",this);//右对齐
        QAction *action15 = new QAction(QIcon(":/Editor/underline.ico"),"下划线",this);//下划线
        QAction *action16 = new QAction(QIcon(":/Editor/color.ico"),"字体颜色",this);//颜色
        QAction *action17 = new QAction(QIcon(":/Editor/font.ico"),"字体",this);//字体
        QAction *action18 = new QAction(QIcon(":/Editor/help.ico"),"帮助",this);//帮助

        QAction *action19 = new QAction(QIcon(":/Editor/pdf.ico"),"导出为PDF",this);
        QAction *action20 = new QAction(QIcon(":/Editor/eraser.ico"),"清除格式",this);
        QAction *action21 = new QAction(QIcon(":/Editor/strike_out.ico"),"删除线",this);
        QAction *action22 = new QAction(QIcon(":/Editor/link.ico"),"链接",this);
        QAction *action23 = new QAction(QIcon(":/Editor/background_color.ico"),"字体背景色",this);
        QAction *action24 = new QAction(QIcon(":/Editor/list.ico"),"列表1",this);
        QAction *action25 = new QAction(QIcon(":/Editor/list-1.ico"),"列表2",this);
        QAction *action26 = new QAction(QIcon(":/Editor/indent.ico"),"增加缩进",this);
        QAction *action27 = new QAction(QIcon(":/Editor/indent-1.ico"),"减少缩进",this);
        QAction *action28 = new QAction(QIcon(":/Editor/picture.ico"),"插入图片",this);
        QAction *action29 = new QAction(QIcon(":/Editor/split-page.ico"),"分页",this);
        QAction *action30 = new QAction(QIcon(":/Editor/split-paragraph.ico"),"分段",this);
        QAction *action31 = new QAction(QIcon(":/Editor/Html.ico"),"导出为Html",this);
        QAction *action32 = new QAction(QIcon(":/Editor/rtf.ico"),"导出为rtf",this);
        QAction *action33 = new QAction(QIcon(":/Editor/markdown.ico"),"导出为markdown",this);
        QAction *action34 = new QAction(QIcon(":/Editor/resize.ico"),"设置行间距和页边距",this);
        QAction *action35 = new QAction(QIcon(":/Editor/coding.ico"),"Start Coding",this);
        QAction *action36 = new QAction(QIcon(":/Editor/normal.ico"),"Back Normal",this);
        QAction *action37 = new QAction(QIcon(":/Editor/moon.ico"),"切换模式",this);
        QAction *action38 = new QAction(QIcon(":/Editor/compile.ico"),"编译",this);
        QAction *action39 = new QAction(QIcon(":/Editor/run.ico"),"运行",this);
        QAction *action40 = new QAction(QIcon(":/Editor/compilenrun.ico"),"编译运行",this);
        QAction *action41 = new QAction(QIcon(":/Editor/stepinto.ico"),"Step into",this);
        QAction *action42 = new QAction(QIcon(":/Editor/stepout.ico"),"Step out",this);
        QAction *action43 = new QAction(QIcon(":/Editor/stepover.ico"),"Step over",this);

                
        //创建状态栏
        QStatusBar *status = new QStatusBar(this);
        //创建标签
        QLabel *statusLabel = new QLabel("Normal Edit", this);

        //创建文本编辑框 显示文本
        QTextEditHighlighter *textEdit = new QTextEditHighlighter(this);

        //创建语法高亮
        Highlighter *highlighter;

        //更改文件编码
        QPushButton *decodeButton;

        // QComboBox *encodingComboBox;

    public slots:
        void showDialog();
        void on_actionexit_triggered();//退出操作
    
        void on_actionopenfile_triggered();//打开文件操作
    
        void on_ServeFile_triggered();//保存文件操作

        void on_actionne_triggered();//创建新文件操作
    
        void on_actionundo_triggered();//撤回操作
    
        void on_actionredo_triggered();//恢复文件
    
        void on_actioncut_triggered();//剪切文件
    
        void on_actioncopy_triggered();//复制文件
    
        void on_actionpatse_triggered();//粘贴文件
    
        void on_actionTextUnderLine_triggered();//下划线
    
        void on_actionTextItalic_triggered();//斜体
    
        void on_actionTextBold_triggered();//粗体
    
        //对齐
        void on_actionLift_triggered();//左对齐
    
        void on_actionCenter_triggered();//居中对齐
    
        void on_actionRight_triggered();//右对齐
    
        void on_actioncolor_triggered();//颜色操作
    
        void on_actionfont_triggered();//字体操作
    
        void on_about();//关于

        void on_actionpdf_triggered();

        void on_actionhtml_triggered();

        void on_actionrtf_triggered();

        void on_actionmarkdown_triggered();

        void textRemoveFormat();

        void textStrikeout();

        void textSize(const QString &p);

        void textLink();

        void textFgColor();

        void textBgColor();

        void listBullet();

        void listOrdered();                     

        void increaseIndentation();

        void decreaseIndentation();

        void insertImage();

        void splitPage()
        {
            textEdit->textCursor().insertHtml("<hr /><hr /><br />");
        }
        void splitPragraph(){textEdit->insertHtml("<hr /><br />");}

        void list(bool checked, QTextListFormat::Style style);

        void indent(int delta);

        void applySettings(double lineSpacing, int margin);

        void start_coding();
         
        void back_normal();

        void change_editor_mood();

        void on_actioncomplie_triggered();

        void on_actionrun_triggered();

        void on_actioncomplieANDrun_triggered();

        void onDecodeButtonClicked();

};