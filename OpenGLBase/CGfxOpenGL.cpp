#include "stdafx.h"


//禁止把单精度变双精度
#pragma warning(disable:4305)

void ShowFloat(float f) {
	TCHAR a[32];
	swprintf(a, 32, _T("%f"), f);

	MessageBox(NULL, a, _T("Test"), MB_OK);
}

CGfxOpenGL::CGfxOpenGL() {

}

CGfxOpenGL::~CGfxOpenGL() {

}

bool CGfxOpenGL::Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	m_angle = 0.0f;

	//glEnable(GL_DEPTH_TEST);//深度测试，近的挡住远的

	//GLfloat pointSize;
	//glGetFloatv(GL_POINT_SIZE, &pointSize);//点的大小，单位为像素
	//ShowFloat(pointSize);

	if (!glIsEnabled(GL_POINT_SMOOTH)) {
		glEnable(GL_POINT_SMOOTH);//对 GL_POINST 点 做平滑处理，显示成圆形。否则会是方形
	}

	GLfloat sizes[2];
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);//启用点的平滑处理后，OpenGL对点的大小有要求，小于或大于这个边界的点，处理就有问题
	GLfloat minPointSize = sizes[0];
	GLfloat maxPointSize = sizes[1];
	//ShowFloat(minPointSize);
	//ShowFloat(maxPointSize);

	GLfloat granularity;//颗粒度
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &granularity);
	//ShowFloat(granularity);//0.125(应该是像素)这个间隔的点 画出来的效果最好。启用平滑处理后，画点的时候，点的大小会被OpenGL做成颗粒度的倍数


	//  1 / (a + b*d + c*d²)衰减系数   d为距离  默认a=1 b=0 c=0
	GLfloat att[3] = { 0.0, 0.0, 0.1 };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, att);//改变点的距离衰减
														   //glPointParameteri(GL_POINT_SIZE_MAX, 2f);//衰减时，可以设置最大点大小 最小点大小 GL_POINT_FADE_THRESHOLD小的看不清 大的能看清的渐变

														   //画线时也有线的粗细，斜线会出现锯齿。GL_LINE_SMOOTH可以设置抗锯齿
														   //抗锯齿也有区间，也有颗粒度

	return true;
}

bool CGfxOpenGL::Shutdown() {
	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height) {


	if (height == 0) {
		height = 1;
	}

	glViewport(0, 0, width, height);//设置OpenGL视口大小。看得见的区域。OpenGL可以很大
	glMatrixMode(GL_PROJECTION);//设置投影矩阵
	glLoadIdentity();//投影矩阵复位

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);//透视，近大远小。近裁剪面，远裁剪面。

	glMatrixMode(GL_MODELVIEW);//模型视图矩阵
	glLoadIdentity();

	m_windowWidth = width;
	m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt) {
	m_angle = m_angle + 0.1f;
	if (m_angle >= 360.0f) {
		m_angle = 0.0f;
	}
}

void CGfxOpenGL::Render() {
	//3D绘图
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空背景。变黑
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	//glTranslatef(0.0f, 0.0f, -5.0f);
	//glRotated(m_angle, 0.0f, 0.0f, 1.0f);//绕着z轴转

	//glColor3f(7.0f, 1.0f, 0.3f);

	//float pointSize = 0.5f;
	//for (float point = -4.0f; point < 5.0f; point += 0.5f) {
	//	glPointSize(pointSize);

	//	glBegin(GL_POINTS);
	//	    //glVertex3f(0.0f, 0.0f, 0.0f);
	//		//glVertex2i((GLint)point, 0);
	//		GLfloat p[3] = {point, 0.0f, 0.0f};
	//		glVertex3fv(p);
	//	glEnd();

	//	pointSize += 1.0f;
	//}


	/*glBegin(GL_TRIANGLES);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();*/


	/*glPointSize(9.5f);
	glBegin(GL_POINTS);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f( 1.0f, 0.0f, -2.0f);
	glEnd();*/

	//glEnable(GL_LINE_STIPPLE);//画虚线

	//glLineStipple(2, 0xAAAA);//1010 1010 1010 1010  虚线像素是否显示 和这个序列是相反的。第一个参数2，是每一位重复的次数 11001100 11001100 ..
	//						 //目前表示 2个像素画 2个像素不画

	//glLineWidth(6.55);
	//glBegin(GL_LINES);
	//glVertex3f(-5.0f, 0.0f, 0.0f);
	//glVertex3f(5.0f, 0.0f, -2.0f);
	//glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);//正面、线框的样式。默认GL_FRONT_AND_BACK,GL_FILL
	//glCullFace(GL_BACK);//指定要剔除的面为背面。背面不画
	//glEnable(GL_CULL_FACE);//启动“剔除面”
	//glFrontFace(GL_CW);//设置正面，为顺时针。默认是GL_CCW与三角形画的顺序有关
	//glBegin(GL_TRIANGLES);//GL_TRIANGLE_STRIP三角形带（逆时针画三角形） GL_TRIANGLE_FAN（扇形）起点公用
	//glEdgeFlag(GL_TRUE);//控制边显不显示
	//glVertex3f(0.0, 5.0, 0.0);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(3.0, 5.0, 0.0);
	//glEnd();

	//GL_QUADS四边形
	//GL_QUAD_STRIP四边形带 有顺序的  上下上下
	//GL_POLYGON逆时针方向连续多个定点

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 5.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(3.0, 5.0, 0.0);
	glEnd();
}