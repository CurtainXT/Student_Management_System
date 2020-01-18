#pragma once
#include<string>
#include<vector>
#include<iostream>

// 用户类
class User
{

};

// 管理员类
class Manager : public User
{
public:
	Manager() = default;
	Manager(std::string userName, std::string password):
	userName(userName), password(password) { }

	// 返回管理员用户名
	std::string GetName() const
	{
		return userName;
	}
	// 返回管理员密码
	std::string GetPassword() const
	{
		return password;
	}
private:
	std::string userName;
	std::string password;
};

// 学生类 描绘学生基本信息
class Student : public User
{
public:
	// Student类构造函数
	Student() = default;
	Student(std::string m, std::string clNum, std::string sID, std::string name, std::string password = "123") :
		m_major(m), m_classNum(clNum), m_studentID(sID), m_name(name), m_password(password) { }

	// 返回学生专业
	std::string GetMajor() const
	{
		return m_major;
	}
	// 返回学生班级
	std::string GetClassNum() const
	{
		return m_classNum;
	}
	// 返回学生密码
	std::string GetPassword() const
	{
		return m_password;
	}
	// 返回学生学号
	std::string GetID() const
	{
		return m_studentID;
	}
	// 返回学生姓名
	std::string GetName() const
	{
		return m_name;
	}

private:
	// 专业
	std::string m_major;
	// 班级
	std::string m_classNum;
	// 学号
	std::string m_studentID;
	// 姓名
	std::string m_name;
	// 登录密码
	std::string m_password;
};

// 课程类 描绘课程信息
class Course	
{
public:
	// Course类构造函数
	Course() = default;
	Course(std::string cNum, std::string coName, int c, int lim, int p, std::string t) :
		m_courseNum(cNum), m_courseName(coName), m_credit(c), m_limit(lim), m_population(p), m_teacher(t) { }
	Course(std::string cNum, std::string coName, int c, std::string t) :
		m_courseNum(cNum), m_courseName(coName), m_credit(c), m_limit(0), m_population(0), m_teacher(t) { }

	// 选课人数加一
	void AddOnePopulation() { m_population++; }
	// 选课人数减一
	void MinusOnePopulation() { m_population--; }
	// 该课程满了吗？
	bool isFull() const
	{
		return (m_population >= m_limit);
	}
	// 返回课程编号
	std::string GetCourseNum() const
	{
		return m_courseNum;
	}
	// 返回课程名称
	std::string GetCourseName() const
	{
		return m_courseName;
	}
	// 返回课程学分信息
	int GetCourseCredit() const
	{
		return m_credit;
	}
	// 返回课程人数上限
	int GetCourseLimit() const
	{
		return m_limit;
	}
	// 返回课程已选人数
	int GetCoursePop() const
	{
		return m_population;
	}
	// 返回教师姓名
	std::string GetTeacherName() const
	{
		return m_teacher;
	}
	// 修改教师姓名
	void SetTeacherName(std::string t) 
	{
		this->m_teacher = t;
	}
	// 修改课程编号
	void SetCourseNum(std::string num)
	{
		this->m_courseNum = num;
	}
	// 修改课程名称
	void SetCourseName(std::string name)
	{
		this->m_courseName = name;
	}
	// 修改课程学分信息
	void SetCourseCredit(int c)
	{
		this->m_credit = c;
	}

private:
	// 课程编号
	std::string m_courseNum;
	// 课程名称
	std::string m_courseName;
	// 学分
	int m_credit;
	// 人数上限
	int m_limit;
	// 已选人数
	int m_population;
	// 授课老师
	std::string m_teacher;
};

// 学生类选课
class StudentCourse:public Student, public Course
{
public:
	// StudentCourse类构造函数
	StudentCourse() = default;
	StudentCourse(std::string m, std::string clNum, std::string sID, std::string name,
		int scn = 0) : Student(m, clNum, sID, name), Course(), selectedCourseNum(scn)
	{ }
	StudentCourse(std::string m, std::string clNum, std::string sID, std::string name,
		std::vector<Course> courses, int scn = 0) : Student(m, clNum, sID, name), Course(),
		selectedCourses(courses), selectedCourseNum(scn)
	{ 
		this->selectedCourseNum = selectedCourses.size();
	}

	// 获得总学分数 
	int GetTotalCredits() const
	{
		int temp = 0;
		for (size_t i = 0; i < selectedCourses.size(); i++)
		{
			temp += selectedCourses[i].GetCourseCredit();
		}
		return temp;
	}

	// 获得总已选课程数
	int GetSelectedCourseNum() const
	{
		return selectedCourseNum;
	}

	// 总已选课程数加一
	void AddOneSeletedCourseNum()
	{
		selectedCourseNum++;
	}

	// 总已选课程数减一
	void MinusOneSeletedCourseNum()
	{
		selectedCourseNum--;
	}

	// 已选课程
	std::vector<Course> selectedCourses;
private:
	// 已选课数
	int selectedCourseNum;
};

class ManagerData
{
public:
	// 保存所有管理员信息
	std::vector<Manager> data;
};

class StudentData
{
public:
	// 保存所有的学生信息
	std::vector<Student> data;
};

class CourseData
{
public:
	// 保存所有的课程信息
	std::vector<Course> data;
};

class StudentCourseData
{
public:
	// 保存所有的学生课程信息
	std::vector<StudentCourse> data;
};

// 学生模块工具方法
class StudentModuleTools
{
public:
	// 查看备选课程信息
	void CheckOptionalCourses(const CourseData& data);
	// 按照课程编号选课
	void SelectCourse(CourseData& cData, StudentCourseData& scData, const Student& user);
	// 查看已选课程信息和累计学分
	void CheckSelected_n_totalCred(const StudentCourseData& scData, const Student& user);
	// 修改密码
	// 。。。
};

// 管理员模块工具方法
class ManagerModuleTools
{
public:
	// 增加学生信息
	void Manage_Add(StudentData &, StudentCourseData &);
	// 删除学生信息
	void Manage_Delete(StudentData& sData, StudentCourseData& scData, CourseData& cData);
	// 修改学生信息
	void Manage_Change(StudentData& sData, CourseData& cData, StudentCourseData& scData);
	// 查找学生信息
	void Manage_CheckStudentData(const StudentData& sData);

	// 增加课程信息
	void Manage_Add(CourseData& cData);
	// 删除课程信息
	void Manage_Delete(CourseData& cData, StudentCourseData& scData);
	// 修改课程信息
	void Manage_Change(CourseData& cData, StudentCourseData& scData);
	// 查找课程信息
	void Manage_CheckCourseData(const CourseData& cData);

	// 查看选课信息
	void Manage_CheckStudentCourseData(const StudentCourseData& scData);
};

// 登录前问候
bool Log();

// 登录系统
bool Register(const StudentData & sData, const ManagerData & mData, const User*(* user));

// 学生模块登录系统
const Student* StudentRegister(const StudentData & data);

// 管理员模块登录系统
const Manager* ManagerRegister(const ManagerData & data);

// 学生密码验证
bool Verification(const Student & user, const std::string password);

// 管理员密码验证
bool Verification(const ManagerData & data, const std::string password);

// 查找学生是否存在
const Student* FindStudent(const std::string stuID, const StudentData& data);

// 查找管理员是否存在
const Manager* FindManager(const ManagerData& data);

// 学生系统选项
void StudentSystem(StudentModuleTools, CourseData& cData, StudentCourseData& scData, Student s);

// 管理员系统选项
void ManagerSystem(ManagerModuleTools, StudentData& sData, ManagerData& mData, CourseData& cData, StudentCourseData& scData, Manager m);