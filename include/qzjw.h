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
		// 课程信息
		struct Course
		{
			// 课程名称
			string Name;
			// 上课时间
			string StartTime;
			// 结束时间
			string EndTime;
			// 开课周次
			string Schedule;
			// 讲师姓名
			string Instructor;
			// 教室名称
			string Classroom;
			// 上课星期(1~7)
			int Week;
			// 第N讲(1~6), TODO: 更换合适的名称
			int Lesson;
		};
		// 考试结果
		struct ExamResult
		{
			// 课程名称
			string Name;
			// 学期
			string Semester;
			// 课程类别(必修/选修)
			string CourseCategory;
			// 课程性质(通识教育课)
			string CourseNature;
			// 考试性质(正常考试、补考、重修)
			string ExamNature;
			// 成绩
			int Score;
			// 学分
			int Credit;
		};

		/**
		 * \brief 初始化教务系统类
		 * \param api_prefix 教务系统地址前缀
		 */
		explicit Jw(const string& api_prefix) :api_prefix_(api_prefix)
		{
		}
		/**
		 * \brief 登录教务系统
		 * \param uid 学号
		 * \param pwd 密码
		 * \return 始终为 true，有错误会抛出异常
		 */
		bool Login(const string& uid, const string& pwd);
		vector<Course> GetCourses(const string&, int week, const string& semester = "");
		vector<ExamResult> GetExamResult(const string& uid, const string& semester = "");
		string GetToken() const
		{
			return token_;
		}
	private:
		string api_prefix_;
		string token_;
	};
}

#endif // !QZJW_CPP_SDK_QZJW_H_H_
