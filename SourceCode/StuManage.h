#pragma once
#include<string>
#include<vector>
#include<iostream>

// �û���
class User
{

};

// ����Ա��
class Manager : public User
{
public:
	Manager() = default;
	Manager(std::string userName, std::string password):
	userName(userName), password(password) { }

	// ���ع���Ա�û���
	std::string GetName() const
	{
		return userName;
	}
	// ���ع���Ա����
	std::string GetPassword() const
	{
		return password;
	}
private:
	std::string userName;
	std::string password;
};

// ѧ���� ���ѧ��������Ϣ
class Student : public User
{
public:
	// Student�๹�캯��
	Student() = default;
	Student(std::string m, std::string clNum, std::string sID, std::string name, std::string password = "123") :
		m_major(m), m_classNum(clNum), m_studentID(sID), m_name(name), m_password(password) { }

	// ����ѧ��רҵ
	std::string GetMajor() const
	{
		return m_major;
	}
	// ����ѧ���༶
	std::string GetClassNum() const
	{
		return m_classNum;
	}
	// ����ѧ������
	std::string GetPassword() const
	{
		return m_password;
	}
	// ����ѧ��ѧ��
	std::string GetID() const
	{
		return m_studentID;
	}
	// ����ѧ������
	std::string GetName() const
	{
		return m_name;
	}

private:
	// רҵ
	std::string m_major;
	// �༶
	std::string m_classNum;
	// ѧ��
	std::string m_studentID;
	// ����
	std::string m_name;
	// ��¼����
	std::string m_password;
};

// �γ��� ���γ���Ϣ
class Course	
{
public:
	// Course�๹�캯��
	Course() = default;
	Course(std::string cNum, std::string coName, int c, int lim, int p, std::string t) :
		m_courseNum(cNum), m_courseName(coName), m_credit(c), m_limit(lim), m_population(p), m_teacher(t) { }
	Course(std::string cNum, std::string coName, int c, std::string t) :
		m_courseNum(cNum), m_courseName(coName), m_credit(c), m_limit(0), m_population(0), m_teacher(t) { }

	// ѡ��������һ
	void AddOnePopulation() { m_population++; }
	// ѡ��������һ
	void MinusOnePopulation() { m_population--; }
	// �ÿγ�������
	bool isFull() const
	{
		return (m_population >= m_limit);
	}
	// ���ؿγ̱��
	std::string GetCourseNum() const
	{
		return m_courseNum;
	}
	// ���ؿγ�����
	std::string GetCourseName() const
	{
		return m_courseName;
	}
	// ���ؿγ�ѧ����Ϣ
	int GetCourseCredit() const
	{
		return m_credit;
	}
	// ���ؿγ���������
	int GetCourseLimit() const
	{
		return m_limit;
	}
	// ���ؿγ���ѡ����
	int GetCoursePop() const
	{
		return m_population;
	}
	// ���ؽ�ʦ����
	std::string GetTeacherName() const
	{
		return m_teacher;
	}
	// �޸Ľ�ʦ����
	void SetTeacherName(std::string t) 
	{
		this->m_teacher = t;
	}
	// �޸Ŀγ̱��
	void SetCourseNum(std::string num)
	{
		this->m_courseNum = num;
	}
	// �޸Ŀγ�����
	void SetCourseName(std::string name)
	{
		this->m_courseName = name;
	}
	// �޸Ŀγ�ѧ����Ϣ
	void SetCourseCredit(int c)
	{
		this->m_credit = c;
	}

private:
	// �γ̱��
	std::string m_courseNum;
	// �γ�����
	std::string m_courseName;
	// ѧ��
	int m_credit;
	// ��������
	int m_limit;
	// ��ѡ����
	int m_population;
	// �ڿ���ʦ
	std::string m_teacher;
};

// ѧ����ѡ��
class StudentCourse:public Student, public Course
{
public:
	// StudentCourse�๹�캯��
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

	// �����ѧ���� 
	int GetTotalCredits() const
	{
		int temp = 0;
		for (size_t i = 0; i < selectedCourses.size(); i++)
		{
			temp += selectedCourses[i].GetCourseCredit();
		}
		return temp;
	}

	// �������ѡ�γ���
	int GetSelectedCourseNum() const
	{
		return selectedCourseNum;
	}

	// ����ѡ�γ�����һ
	void AddOneSeletedCourseNum()
	{
		selectedCourseNum++;
	}

	// ����ѡ�γ�����һ
	void MinusOneSeletedCourseNum()
	{
		selectedCourseNum--;
	}

	// ��ѡ�γ�
	std::vector<Course> selectedCourses;
private:
	// ��ѡ����
	int selectedCourseNum;
};

class ManagerData
{
public:
	// �������й���Ա��Ϣ
	std::vector<Manager> data;
};

class StudentData
{
public:
	// �������е�ѧ����Ϣ
	std::vector<Student> data;
};

class CourseData
{
public:
	// �������еĿγ���Ϣ
	std::vector<Course> data;
};

class StudentCourseData
{
public:
	// �������е�ѧ���γ���Ϣ
	std::vector<StudentCourse> data;
};

// ѧ��ģ�鹤�߷���
class StudentModuleTools
{
public:
	// �鿴��ѡ�γ���Ϣ
	void CheckOptionalCourses(const CourseData& data);
	// ���տγ̱��ѡ��
	void SelectCourse(CourseData& cData, StudentCourseData& scData, const Student& user);
	// �鿴��ѡ�γ���Ϣ���ۼ�ѧ��
	void CheckSelected_n_totalCred(const StudentCourseData& scData, const Student& user);
	// �޸�����
	// ������
};

// ����Աģ�鹤�߷���
class ManagerModuleTools
{
public:
	// ����ѧ����Ϣ
	void Manage_Add(StudentData &, StudentCourseData &);
	// ɾ��ѧ����Ϣ
	void Manage_Delete(StudentData& sData, StudentCourseData& scData, CourseData& cData);
	// �޸�ѧ����Ϣ
	void Manage_Change(StudentData& sData, CourseData& cData, StudentCourseData& scData);
	// ����ѧ����Ϣ
	void Manage_CheckStudentData(const StudentData& sData);

	// ���ӿγ���Ϣ
	void Manage_Add(CourseData& cData);
	// ɾ���γ���Ϣ
	void Manage_Delete(CourseData& cData, StudentCourseData& scData);
	// �޸Ŀγ���Ϣ
	void Manage_Change(CourseData& cData, StudentCourseData& scData);
	// ���ҿγ���Ϣ
	void Manage_CheckCourseData(const CourseData& cData);

	// �鿴ѡ����Ϣ
	void Manage_CheckStudentCourseData(const StudentCourseData& scData);
};

// ��¼ǰ�ʺ�
bool Log();

// ��¼ϵͳ
bool Register(const StudentData & sData, const ManagerData & mData, const User*(* user));

// ѧ��ģ���¼ϵͳ
const Student* StudentRegister(const StudentData & data);

// ����Աģ���¼ϵͳ
const Manager* ManagerRegister(const ManagerData & data);

// ѧ��������֤
bool Verification(const Student & user, const std::string password);

// ����Ա������֤
bool Verification(const ManagerData & data, const std::string password);

// ����ѧ���Ƿ����
const Student* FindStudent(const std::string stuID, const StudentData& data);

// ���ҹ���Ա�Ƿ����
const Manager* FindManager(const ManagerData& data);

// ѧ��ϵͳѡ��
void StudentSystem(StudentModuleTools, CourseData& cData, StudentCourseData& scData, Student s);

// ����Աϵͳѡ��
void ManagerSystem(ManagerModuleTools, StudentData& sData, ManagerData& mData, CourseData& cData, StudentCourseData& scData, Manager m);