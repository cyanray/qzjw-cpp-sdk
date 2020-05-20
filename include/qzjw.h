#pragma once
#ifndef QZJW_CPP_SDK_QZJW_H_H_
#define QZJW_CPP_SDK_QZJW_H_H_
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace cyanray
{
	class Jw
	{
	public:
		// �γ���Ϣ
		struct Course
		{
			// �γ�����
			string Name;
			// �Ͽ�ʱ��
			string StartTime;
			// ����ʱ��
			string EndTime;
			// �����ܴ�
			string Schedule;
			// ��ʦ����
			string Instructor;
			// ��������
			string Classroom;
			// �Ͽ�����(1~7)
			int Week;
			// ��N��(1~6), TODO: �������ʵ�����
			int Lesson;
		};
		// ���Խ��
		struct ExamResult
		{
			// �γ�����
			string Name;
			// ѧ��
			string Semester;
			// �γ����(����/ѡ��)
			string CourseCategory;
			// �γ�����(ͨʶ������)
			string CourseNature;
			// ��������(�������ԡ�����������)
			string ExamNature;
			// �ɼ�
			int Score;
			// ѧ��
			int Credit;
		};
		Jw(const string& api_prefix);
		/**
		 * \brief ��¼����ϵͳ
		 * \param uid ѧ��
		 * \param pwd ����
		 * \return ʼ��Ϊ true���д�����׳��쳣
		 */
		bool Login(const string& uid, const string& pwd);
		vector<Course> GetCourses(const string&, int week, const string& semester = "");
		vector<ExamResult> GetExamResult(const string& uid, const string& semester = "");
	private:
		string api_prefix_;
		string token_;
	};
}

#endif // !QZJW_CPP_SDK_QZJW_H_H_
