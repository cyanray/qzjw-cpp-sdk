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
			// 从第N讲开始(1~6), TODO: 更换合适的名称
			int StartLesson;
			// 到第N讲结束(1~6), TODO: 更换合适的名称
			int EndLesson;
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
			// 成绩
			string Score;
			// 学分
			double Credit;
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
		/**
		 * \brief 获取课表
		 * \param uid 学号
		 * \param week 周次
		 * \param semester 学期(如：2019-2020-2)，留空为当前学期 
		 * \return vector<Course>，出错会抛出异常
		 */
		vector<Course> GetCourses(const string& uid, int week, const string& semester = "");
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
