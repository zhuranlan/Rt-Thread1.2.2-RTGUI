#include <rtthread.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/window.h>
#include <rtgui/dc.h>
#include <rtgui/font.h>
#include <rtgui/widgets/button.h>
#include <rtgui/image.h>
#include <rtgui/widgets/edit.h>

static	struct rtgui_edit *edit;
struct rtgui_win *win1;

static void button_click(struct rtgui_object *object, struct rtgui_event *event)
{
    rt_int32_t idx;
	struct edit_line *line;

    //rtgui_edit_append_line(edit,"11111111111");
    line = rtgui_edit_get_line_by_index(edit, rtgui_edit_get_current_point(edit).y);
    idx = rtgui_edit_get_index_by_line(edit, line);
    RT_ASSERT(idx == rtgui_edit_get_current_point(edit).y);
    for (; idx >= 0; idx--)
    {
        rt_kprintf("D %d\n", idx);
        rtgui_edit_delete_line(edit, rtgui_edit_get_line_by_index(edit, idx));
    }
    //rtgui_edit_insert_line(edit,line,"2222222222222");
}

static void button1_click(struct rtgui_object *object, struct rtgui_event *event)
{
	struct edit_line *line = rtgui_edit_get_line_by_index(edit,rtgui_edit_get_current_point(edit).y);

    rtgui_edit_append_line(edit,"11111111111");
    rtgui_edit_insert_line(edit,line,"2222222222222");
    rtgui_edit_delete_line(edit,line);
	rtgui_edit_set_text(edit,
                        "1һ�����������߰˾�ʮ���ұ����켺�����ɹ��ӳ���������δ�����纥һ\n"
                        "һ2�����������߰˾�ʮ���ұ����켺�����ɹ��ӳ���������\n"
                        "3һ�����������߰˾�ʮ���ұ����켺�����ɹ��ӳ���12345678������δ�����纥һ��������\n"
                        "һ4�����������߰˾�ʮ���ұ����켺�����ɹ��ӳ���������δ�����纥һ����\n"
                        "1234567890123456789012345678901234567890������12345678���ұ����켺����\n"
                        "5һ�����������߰˾�ʮ��abc\n"
                        "һ6�����������ߡ��š��ף������켺�����ɹ��ӳ���\n"
                        "7һ����������assault���ұ����켺����\n"
                        "һ8����\n"
                        "9һ����������12345678���ұ����켺����\n");
	//rtgui_edit_append_line(edit,"11111111111");
	//rtgui_widget_update(RTGUI_WIDGET(edit));
}
static void button2_click(struct rtgui_object *object, struct rtgui_event *event)
{
	rtgui_edit_set_text(edit, "");
}

void edit_print_test(void)
{
#define P rt_kprintf
    P("1, �ڿհ�״̬�µ�� edit �ؼ���Ӧ���ڵ�һ�е�һ����ʾ��ꡣ\n");
    P("2, �����ַ�����\n");
    P("3, ��ס SHIFT ֮�������д�ַ�����\n");
    P("4, �� CAPSLOCK�������дģʽ��֮�������д�ַ�����\n");
    P("5, �ٰ� CAPSLOCK���Ƴ���дģʽ��֮������Сд�ַ�����\n");
#undef P
}

static void _dump_delete(struct rtgui_edit *edit, struct edit_line *line)
{
    rt_kprintf("deleting %d: %s\n", line->line_number, line->text);
}

void win1_ui_init(void)
{
    rtgui_rect_t rect = {0, 0, 480, 272};

    struct rtgui_button *button,*button1,*button2;

    {
        win1 = rtgui_win_create(RT_NULL, "win1", &rect, RTGUI_WIN_STYLE_MAINWIN
                                | RTGUI_WIN_STYLE_NO_BORDER |
                                RTGUI_WIN_STYLE_NO_TITLE);
    }
    {
        button=rtgui_button_create("abc");
        rect.x1=50;
        rect.x2=rect.x1+50;
        rect.y1=240;
        rect.y2=rect.y1+20;
        rtgui_widget_set_rect(RTGUI_WIDGET(button),&rect);
        rtgui_button_set_onbutton(button,button_click);
        RTGUI_WIDGET_FLAG(button)&=~RTGUI_WIDGET_FLAG_FOCUSABLE;
        rtgui_container_add_child(RTGUI_CONTAINER(win1),RTGUI_WIDGET(button));

    }
    {
        button1=rtgui_button_create("abc");
        rect.x1=150;
        rect.x2=rect.x1+50;
        rect.y1=240;
        rect.y2=rect.y1+20;
        rtgui_widget_set_rect(RTGUI_WIDGET(button1),&rect);
        rtgui_button_set_onbutton(button1,button1_click);
        RTGUI_WIDGET_FLAG(button1)&=~RTGUI_WIDGET_FLAG_FOCUSABLE;
        rtgui_container_add_child(RTGUI_CONTAINER(win1),RTGUI_WIDGET(button1));
    }
    {
        button2=rtgui_button_create("���");
        rect.x1=250;
        rect.x2=rect.x1+50;
        rect.y1=240;
        rect.y2=rect.y1+20;
        rtgui_widget_set_rect(RTGUI_WIDGET(button2),&rect);
        rtgui_button_set_onbutton(button2,button2_click);
        RTGUI_WIDGET_FLAG(button2)&=~RTGUI_WIDGET_FLAG_FOCUSABLE;
        rtgui_container_add_child(RTGUI_CONTAINER(win1),RTGUI_WIDGET(button2));

    }
    {
        button2=rtgui_button_create("dummy");
        rect.x1=350;
        rect.x2=rect.x1+50;
        rect.y1=240;
        rect.y2=rect.y1+20;
        rtgui_widget_set_rect(RTGUI_WIDGET(button2),&rect);
        rtgui_container_add_child(RTGUI_CONTAINER(win1),RTGUI_WIDGET(button2));
    }
    {
        edit=rtgui_edit_create(RTGUI_CONTAINER(win1),10,10,408,200);
        rtgui_edit_set_ondelete_line(edit, _dump_delete);
    }
    rtgui_win_show(win1, RT_TRUE);
}

int dump_edit(void)
{
    rtgui_edit_dump(edit);
    return 0;
}
FINSH_FUNCTION_EXPORT(dump_edit, dump the edit);


extern void win1_ui_init(void);
void test_main(void)
{

    struct rtgui_app *application;

    application = rtgui_app_create("test");
    if (RT_NULL == application)
    {
        rt_kprintf("create application \"test\" failed!\n");
        return ;
    }
	//rtgui_font_system_init();
    win1_ui_init();
    rtgui_app_run(application);
    rtgui_app_destroy(application);
}
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif
FINSH_FUNCTION_EXPORT(test_main, test run)

