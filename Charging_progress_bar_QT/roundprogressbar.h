// roundprogressbar.h
#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class RoundProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float _value READ getValue WRITE _setValue)

public:
    enum ControlFlags {
        outterCirle = 0x01,
        linearColor = 0x02,
        decorateDot = 0x04,
        defaultText = 0x08
    };

    enum InnerDefaultTextStyle {
        value = 0x01,
        valueAndMax = 0x02,
        percent = 0x03
    };

    explicit RoundProgressBar(QWidget *parent = nullptr);
    ~RoundProgressBar();

    // 设置函数
    void setdefault(int startAngle, bool clockWise);
    void setOutterBarWidth(float width);
    void setInnerBarWidth(float width);
    void setRange(float min, float max);
    void setValue(float value);
    void setOutterColor(const QColor& outterColor);
    void setInnerColor(const QColor& startColor, const QColor& endColor);
    void setInnerColor(const QColor& startColor);
    void setDefaultTextColor(const QColor& textColor);
    void setControlFlags(int flags);
    void setPrecision(int precision);
    void setShadowColor(const QColor &color);
    void setShadowWidth(int width);
    void setRadiusWidth(int width);
    void setCornerRadius(int radius);  // 添加这行

    // 获取函数
    float getValue() const { return _value; }

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    //绘制参数结构体
    struct DrawParams {
        float width;
        QColor color;
        QColor endColor;
        bool isGradient;};

    // 绘制函数
    void drawCircularArc(QPainter& painter, const DrawParams& params, const QRectF& rect, int startAngle, int spanAngle);
    void paintOutterBar(QPainter &painter);
    void paintInnerBar(QPainter& painter);
    void paintDot(QPainter& painter);
    void paintText(QPainter& painter);
    void drawArc(QPainter *painter, int radius, qreal angle);
    void drawGlowText(QPainter *painter);
    void drawText(QPainter& painter, const QString& text, const QFont& font, const QPointF& center);

    //辅助函数
    void caculateSquare();
    int calculateAngle() const;
    QRectF calculateRect(int width) const;
    void _setValue(float value);
    void drawProgress(QPainter& painter);// 添加这行

private:
    // 基本属性
    float _value;
    float _min;
    float _max;
    float _precision;
    int _controlFlags;
    int _margin; // 添加边距属性
    int _cornerRadius;  // 控制进度条圆角的程度

    // 样式相关
    float _outterBarWidth;
    float _innerBarWidth;
    QColor _outterColor;
    QColor _startColor;
    QColor _endColor;
    QColor _textColor;

    // 位置相关
    float _squareWidth;
    float _squareStart;
    float _startAngle;
    bool _clockWise;
    float _dotX;
    float _dotY;// 光晕效果
    QColor shadowColor;
    int shadowWidth;
    int radiusWidth;
    InnerDefaultTextStyle _innerDefaultTextStyle;
};

#endif // ROUNDPROGRESSBAR_H
