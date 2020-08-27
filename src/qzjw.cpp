#include "qzjw.h"
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <CURLWrapper.h>
using namespace Cyan;
using std::stringstream;
using std::runtime_error;
using namespace nlohmann;

namespace cyanray
{
	bool Jw::Login(const string& uid, const string& pwd)
	{
		stringstream url;
		url << api_prefix_
			<< "/app.do?method=authUser&xh="
			<< uid
			<< "&pwd="
			<< pwd;
		HTTP http;
		auto resp = http.Get(url.str());
		if (!resp.Ready) throw runtime_error("请求无响应.");
		if (resp.StatusCode != 200) throw runtime_error("返回非 200 状态码.");
		json re_json = json::parse(resp.Content);
		string flag = re_json["flag"].get<string>();
		if (flag != "1")
		{
			string err_msg = re_json["msg"].get<string>();
		}
		token_ = re_json["token"].get<string>();
		return true;
	}

	vector<Jw::Course> Jw::GetCourses(const string& uid, int week, const string& semester)
	{
		if (token_.empty()) throw runtime_error("尚未登录.");
		stringstream url;
		url << api_prefix_
			<< "/app.do?method=getKbcxAzc&xh="
			<< uid
			<< "&xnxqid="
			<< semester
			<< "&zc="
			<< week;
		HTTP http;
		http.AddHeader("token", token_);
		auto resp = http.Get(url.str());
		if (!resp.Ready) throw runtime_error("请求无响应.");
		if (resp.StatusCode != 200) throw runtime_error("返回非 200 状态码.");
		json re_json = json::parse(resp.Content);
		vector<Course> res;
		// fuck 不走寻常路的json
		if (re_json.size() == 0 || re_json[0].is_null()) return res;
		res.reserve(re_json.size());
		for (auto&& ele : re_json)
		{
			unsigned cweek, lesson1, lesson2;
			string t = ele["kcsj"].get<string>();
			stringstream ss;
			ss.str(t.substr(0, 1));
			ss >> cweek;
			ss.str(t.substr(1, 2));
			ss >> lesson1;
			ss.str(t.substr(2, 2));
			ss >> lesson2;

			Course c;
			try
			{
				c.Name = ele["kcmc"].get<string>();
			}
			catch (...)
			{
				c.Name = "?";
			}
			try
			{
				c.Classroom = ele["jsmc"].get<string>();
			}
			catch (...)
			{
				c.Classroom = "?";
			}
			c.Instructor = ele["jsxm"].get<string>();
			try
			{
				c.StartTime = ele["kssj"].get<string>();
			}
			catch (...)
			{
				c.StartTime = "?";
			}
			try
			{
				c.EndTime = ele["jssj"].get<string>();
			}
			catch (...)
			{
				c.EndTime = "?";
			}
			try
			{
				c.Schedule = ele["kkzc"].get<string>();
			}
			catch (...)
			{
				c.Schedule = "?";
			}
			c.Week = cweek;
			c.StartLesson = lesson1;
			c.EndLesson = lesson2;
			res.push_back(c);
		}
		return res;
	}

	vector<Jw::ExamResult> Jw::GetExamResult(const string& uid, const string& semester)
	{
		if (token_.empty()) throw runtime_error("尚未登录.");
		stringstream url;
		url << api_prefix_
			<< "/app.do?method=getCjcx&xh="
			<< uid
			<< "&xnxqid="
			<< semester;
		HTTP http;
		http.AddHeader("token", token_);
		auto resp = http.Get(url.str());
		if (!resp.Ready) throw runtime_error("请求无响应.");
		if (resp.StatusCode != 200) throw runtime_error("返回非 200 状态码.");
		json re_json = json::parse(resp.Content);
		vector<ExamResult> res;
		// fuck 不走寻常路的json
		if (re_json.size() == 0 || re_json[0].is_null()) return res;
		res.reserve(re_json.size());
		for (auto&& ele : re_json)
		{
			ExamResult exam_result;
			try
			{
				exam_result.Name = ele["kcmc"].get<string>();
				exam_result.Score = ele["zcj"].get<string>();
				exam_result.Credit = ele["xf"].get<double>();
				exam_result.Semester = ele["xqmc"].get<string>();
				exam_result.CourseCategory = ele["kclbmc"].get<string>();
				exam_result.CourseNature = ele["kcxzmc"].get<string>();
			}
			catch (...)
			{
			}
			res.push_back(exam_result);
		}
		return res;
	}

	string Jw::GetMajor(const string& uid)
	{
		stringstream url;
		url << api_prefix_ 
			<<"/app.do?method=getUserInfo&xh="
			<< uid;
		HTTP http;
		http.AddHeader("token", token_);
		auto resp = http.Get(url.str());
		if (!resp.Ready) throw runtime_error("请求无响应.");
		if (resp.StatusCode != 200) throw runtime_error("返回非 200 状态码.");
		json re_json = json::parse(resp.Content);
		return re_json["zymc"];
	}

}
