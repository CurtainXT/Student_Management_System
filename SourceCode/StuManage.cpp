#include"StuManage.h"

/*-------------------------------学生工具组--------------------------------*/
// 查看备选课程信息
void StudentModuleTools::CheckOptionalCourses(const CourseData& data)
{
	// 用于保存所有可以选择的课程信息
	CourseData temp;
	for (size_t i = 0; i < data.data.size(); i++)
	{
		if (!data.data[i].isFull())
		{
			temp.data.push_back(data.data[i]);
		}
	}
	std::cout << std::endl;
	std::cout << "可以选择的课程有：" << std::endl;
	// 打印所有可选课程信息
	for (size_t i = 0; i < temp.data.size(); i++)
	{
		std::cout << temp.data[i].GetCourseNum()
			<< " "
			<< temp.data[i].GetCourseName()
			<< " "
			<< temp.data[i].GetCourseCredit()
			<< " "
			<< temp.data[i].GetTeacherName()
			<< std::endl;
	}
}

// 按照课程编号选课
void StudentModuleTools::SelectCourse(CourseData& cData, StudentCourseData& scData, const Student& user) 
{
	std::cout << std::endl;
	std::cout << "请输入课程编号" << std::endl;
	std::string courseNumTemp;
	std::cin >> courseNumTemp;
	std::cin.get();

	for (size_t i = 0; i < cData.data.size(); i++)
	{
		// 查找该课程编号
		if (cData.data[i].GetCourseNum() == courseNumTemp)
		{
			// 验证该课程是否已满
			if(!cData.data[i].isFull())
			{ 
				// 查找到该用户的学生选课数据
				StudentCourse* user_sc = NULL;
				for (size_t c = 0; c < scData.data.size(); c++)
				{
					if (scData.data[c].GetID() == user.GetID())
					{
						// 如果找到了，添加引用
						user_sc = &(scData.data[c]);
					}
				}

				// 检查选课是否重复
				bool isSelected = false;
				for (size_t i = 0; i < user_sc->selectedCourses.size(); i++)
				{
					// 如果要选择的课程已经被选择
					if (courseNumTemp == (*user_sc).selectedCourses[i].GetCourseNum())
					{
						isSelected = true;
					}
				}
				// 如果没有重复
				if (!isSelected)
				{
					std::cout << "已选择课程：" << std::endl;
					std::cout << cData.data[i].GetCourseNum()
						<< " "
						<< cData.data[i].GetCourseName()
						<< std::endl;
					// 将课程的已选人数加一
					cData.data[i].AddOnePopulation();
					// 将学生选课的总选课数加一
					user_sc->AddOneSeletedCourseNum();
					// 在学生课程数据中添加该选课信息
					user_sc->selectedCourses.push_back(cData.data[i]);
				}
				else
				{
					std::cout << "该课程已经被选择过了" << std::endl;
					break;
				}
			}
			else
			{
				std::cout << "该课程已满" << std::endl;
				break;
			}
		}
	}
}

// 查看已选课程信息和累计学分
void StudentModuleTools::CheckSelected_n_totalCred(const StudentCourseData& scData, const Student& user)
{
	// 查找到该用户的学生选课数据
	const StudentCourse* user_sc = NULL;
	for (size_t c = 0; c < scData.data.size(); c++)
	{
		if (scData.data[c].GetID() == user.GetID())
		{
			// 如果找到了，添加引用
			user_sc = &(scData.data[c]);
		}
	}
	if (user_sc == NULL)
	{
		std::cout << "未找到该学生的选课信息！" << std::endl;
		return;
	}
	else
	{
		std::cout << "你的已选课程有：" << std::endl;
		if (user_sc->selectedCourses.size() == 0)
		{
			std::cout << "你还没有进行任何选课！" << std::endl;
		}
		else
		{
			for (size_t i = 0; i < user_sc->selectedCourses.size(); i++)
			{
				std::cout << user_sc->selectedCourses[i].GetCourseNum() << " "
					<< user_sc->selectedCourses[i].GetCourseName() << std::endl;
			}
			std::cout << "总共学分为：" << user_sc->GetTotalCredits() << std::endl;
		}
	}
}

/*-------------------------------管理员工具组--------------------------------*/
// 增加学生信息
void ManagerModuleTools::Manage_Add(StudentData& sData, StudentCourseData& scData)
{
	// 想用户获取信息
	std::cout << "请输入要添加的学生信息：" << std::endl;
	std::string data1;
	std::string data2;
	std::string data3;
	std::string data4;
	std::string data5;
	std::cout << "请输入专业：";
	std::cin >> data1;
	std::cout << "请输入班级：";
	std::cin >> data2;
	std::cout << "请输入学号：";
	std::cin >> data3;
	std::cout << "请输入姓名：";
	std::cin >> data4;
	std::cout << "请输入登录密码：";
	std::cin >> data5;
	std::cin.get();

	// 将获得的信息用于构造新的数据对象
	Student stemp(data1, data2, data3, data4, data5);
	StudentCourse sctemp(data1, data2, data3, data4);

	// 将新数据添加到数据容器中
	sData.data.push_back(stemp);
	scData.data.push_back(sctemp);
	std::cout << "添加成功!" << std::endl;
}

// 删除学生信息
void ManagerModuleTools::Manage_Delete(StudentData& sData, StudentCourseData& scData, CourseData& cData)
{
	while (true)
	{
		std::string stuID;
		std::cout << "请输入要删除学生的学号：" << std::endl;
		std::cin >> stuID;
		std::cin.get();

		bool is_stu_success = false;
		bool is_sc_success = false;
		
		for (size_t i = 0; i < sData.data.size(); i++)
		{
			if (sData.data[i].GetID() == stuID)
			{
				// 删除学生数据
				auto iter = sData.data.begin() + i;
				sData.data.erase(iter);
				is_stu_success = true;
				break;
			}
		}
		for (size_t i = 0; i < scData.data.size(); i++)
		{
			if (scData.data[i].GetID() == stuID)
			{
				// 存储课号
				std::vector<std::string> courseNums;
				// 删除之前修改他已选课程的选课人数数据
				for (int c = 0; c < scData.data[i].GetSelectedCourseNum(); c++)
				{
					//拿到所有已选课的课号
					courseNums.push_back(scData.data[i].selectedCourses[c].GetCourseNum());
				}
				for (size_t r = 0; r < courseNums.size(); r++)
				{
					// 将课程的已选人数减一
					for (size_t d = 0; d < cData.data.size(); d++)
					{
						if (courseNums[r] == cData.data[d].GetCourseNum())
						{
							cData.data[d].MinusOnePopulation();
							break;
						}
					}
				}

				// 删除学生选课数据
				auto iter = scData.data.begin() + i;
				scData.data.erase(iter);
				is_sc_success = true;
				break;
			}
		}

		if (is_stu_success && is_sc_success)
		{
			std::cout << "成功删除学生信息！" << std::endl;
			break;
		}
		else
		{
			std::cout << "未找到该学生信息，请重新输入!" << std::endl;
		}
	}
}

// 修改学生信息
void ManagerModuleTools::Manage_Change(StudentData& sData, CourseData& cData, StudentCourseData& scData)
{
	// 找到该用户
	Student* p_stemp = NULL;
	StudentCourse* p_sctemp = NULL;

	while (true)
	{
		std::cout << "请输入想要修改的学生的学号" << std::endl;
		std::string stuID;
		std::cin >> stuID;
		std::cin.get();
		bool is_stu_find = false;
		bool is_sc_find = false;
		// 找到学生数据
		for (size_t i = 0; i < sData.data.size(); i++)
		{
			if (stuID == sData.data[i].GetID())
			{
				is_stu_find = true;
				p_stemp = &(sData.data[i]);
				break;
			}
		}
		// 找到学生选课数据
		for (size_t i = 0; i < scData.data.size(); i++)
		{
			if (stuID == scData.data[i].GetID())
			{
				is_sc_find = true;
				p_sctemp = &(scData.data[i]);

				// 修改数据之前，先将原数据的选课记录删除
				std::vector<std::string> courseNums; // 存储课号
				// 删除之前修改他已选课程的选课人数数据
				for (int c = 0; c < p_sctemp->GetSelectedCourseNum(); c++)
				{
					//拿到所有已选课的课号
					courseNums.push_back(scData.data[i].selectedCourses[c].GetCourseNum());
				}
				for (size_t r = 0; r < courseNums.size(); r++)
				{
					// 将课程的已选人数减一
					for (size_t d = 0; d < cData.data.size(); d++)
					{
						if (courseNums[r] == cData.data[d].GetCourseNum())
						{
							cData.data[d].MinusOnePopulation();
							break;
						}
					}
				}
				break;
			}
		}
		// 确认是否找到了用户
		if (is_stu_find && is_sc_find)
		{
			break;
		}
		else
		{
			std::cout << "没有找到该用户，请重新输入" << std::endl;
		}
	}

	std::cout << "请输入修改以后的数据" << std::endl;
	std::string data1;
	std::string data2;
	std::string data3;
	std::string data4;
	std::string data5;
	std::cout << "请输入专业：";
	std::cin >> data1;
	std::cout << "请输入班级：";
	std::cin >> data2;
	std::cout << "请输入学号：";
	std::cin >> data3;
	std::cout << "请输入姓名：";
	std::cin >> data4;
	std::cout << "请输入登录密码：";
	std::cin >> data5;
	std::cout << "修改成功！" << std::endl;
	Student stemp(data1, data2, data3, data4, data5);
	StudentCourse sctemp(data1, data2, data3, data4);
	*p_stemp = stemp;
	*p_sctemp = sctemp;
}

// 查找学生信息
void ManagerModuleTools::Manage_CheckStudentData(const StudentData& sData)
{
	while (true)
	{
		// 是查看全部还是查看个别
		std::cout << "A - 查看全部" << std::endl;
		std::cout << "B - 查看单个" << std::endl;
		char a = std::cin.get();
		std::cin.get();
		if (a == 'A' || a == 'a')
		{
			for (size_t i = 0; i < sData.data.size(); i++)
			{
				std::cout << sData.data[i].GetMajor()
					<< " "
					<< sData.data[i].GetClassNum()
					<< " "
					<< sData.data[i].GetID()
					<< " "
					<< sData.data[i].GetName()
					<< " "
					<< sData.data[i].GetPassword()
					<< std::endl;
			}
			break;
		}
		else if (a == 'B' || a == 'b')
		{
			std::cout << "请输入要查找的学生学号" << std::endl;
			std::string stuID;
			std::cin >> stuID;
			std::cin.get();

			// 找到该用户
			const Student* p_temp = NULL;
			while (true)
			{
				bool is_find = false;
				for (size_t i = 0; i < sData.data.size(); i++)
				{
					if (stuID == sData.data[i].GetID())
					{
						is_find = true;
						p_temp = &(sData.data[i]);
					}
				}
				if (is_find)
				{
					break;
				}
				else
				{
					std::cout << "没有找到该用户，请重新输入" << std::endl;
				}
			}

			std::cout << "专业：" << p_temp->GetMajor()
				<< std::endl
				<< "班级：" << p_temp->GetClassNum()
				<< std::endl
				<< "学号：" << p_temp->GetID()
				<< std::endl
				<< "姓名：" << p_temp->GetName()
				<< std::endl
				<< "登录密码：" << p_temp->GetPassword();

			break;
		}
		else
		{
			std::cout << "请输入正确字符！" << std::endl;
		}
	}
}

// 增加课程信息
void ManagerModuleTools::Manage_Add(CourseData& cData)
{
	std::string data1;
	std::string data2;
	int data3;
	int data4;
	int data5 = 0;
	std::string data6;
	std::cout << "输入新课程课号" << std::endl;;
	std::cin >> data1;
	std::cout << "输入新课程名称" << std::endl;
	std::cin >> data2;
	std::cout << "输入新课程学分" << std::endl;
	std::cin >> data3;
	std::cout << "输入新课程人数上限" << std::endl;
	std::cin >> data4;
	std::cout << "输入新课程授课老师" << std::endl;
	std::cin >> data6;
	std::cin.get();
	cData.data.push_back(Course(data1, data2, data3, data4, data5, data6));
	std::cout << "添加成功！" << std::endl;
}

//// 删除课程信息
void ManagerModuleTools::Manage_Delete(CourseData& cData, StudentCourseData& scData)
{
	std::cout << "输入要删除课程的课程号" << std::endl;
	std::string courseNum;
	std::cin >> courseNum;
	std::cin.get();

	// 删除所有学生选课中本课程的记录
	for (size_t i = 0; i < scData.data.size(); i++)
	{
		// 如果该学生选了课
		if (scData.data[i].GetSelectedCourseNum() > 0)
		{
			// 查找其中是否有该课程
			for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
			{
				// 如果有，删除选课记录
				if (courseNum == scData.data[i].selectedCourses[c].GetCourseNum())
				{
					auto iter = scData.data[i].selectedCourses.begin() + c;
					scData.data[i].selectedCourses.erase(iter);
					scData.data[i].MinusOneSeletedCourseNum();
					break;
				}
			}
		}
	}
	// 在课程数据容器中找到该课程
	for (size_t i = 0; i < cData.data.size(); i++)
	{
		if (courseNum == cData.data[i].GetCourseNum())
		{
			// 删除它
			auto iter = cData.data.begin() + i;
			cData.data.erase(iter);
			break;
		}
	}
	std::cout << "删除成功！" << std::endl;
}

// 修改课程信息
void ManagerModuleTools::Manage_Change(CourseData& cData, StudentCourseData& scData)
{
	// 找到该课程
	Course* p_ctemp = NULL;

	while (true)
	{
		std::cout << "请输入想要修改的课程编号：" << std::endl;
		std::string courseNum;
		std::cin >> courseNum;
		std::cin.get();
		bool is_course_find = false;
		// 找到课程数据
		for (size_t i = 0; i < cData.data.size(); i++)
		{
			if (courseNum == cData.data[i].GetCourseNum())
			{
				is_course_find = true;
				p_ctemp = &(cData.data[i]);
				break;
			}
		}

		// 修改课程信息
		std::string data1;
		int data2;
		bool is_find = false;
		do
		{
			std::cout << "选择要修改的课程信息" << std::endl;
			std::cout << "A - 课程编号" << std::endl;
			std::cout << "B - 课程名称" << std::endl;
			std::cout << "C - 学分" << std::endl;
			std::cout << "D - 授课老师" << std::endl;

			char a = std::cin.get();
			std::cin.get();
			switch (a)
			{
			case 'A':
			case 'a':
				std::cout << "请输入新的课程编号" << std::endl;
				std::cin >> data1;
				std::cin.get();
				p_ctemp->SetCourseNum(data1);
				is_find = true;
				break;
			case 'B':
			case 'b':
				std::cout << "请输入新的课程名称" << std::endl;
				std::cin >> data1;
				std::cin.get();
				p_ctemp->SetTeacherName(data1);
				is_find = true;
				break;
			case 'C':
			case 'c':
				std::cout << "请输入新的学分" << std::endl;
				std::cin >> data2;
				std::cin.get();
				p_ctemp->SetCourseCredit(data2);
				is_find = true;
				break;
			case 'D':
			case 'd':
				std::cout << "请输入新的授课老师" << std::endl;
				std::cin >> data1;
				std::cin.get();
				p_ctemp->SetTeacherName(data1);
				is_find = true;
				break;
			default:
				std::cout << "请输入正确字符";
				break;
			}
		} while (!is_find);

		// 找到学生选课数据中的所有本课程
		for (size_t i = 0; i < scData.data.size(); i++)
		{
			// 该学生有选课
			if (scData.data[i].GetSelectedCourseNum() > 0)
			{
				// 查找是否选了该课程
				for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
				{
					// 如果选了
					if (scData.data[i].selectedCourses[c].GetCourseNum() == courseNum)
					{
						// 更新课程数据的修改
						scData.data[i].selectedCourses[c] = Course(p_ctemp->GetCourseNum(), p_ctemp->GetCourseName(), p_ctemp->GetCourseCredit(), p_ctemp->GetTeacherName());
						break;
					}
				}
			}
		}
		// 确认是否找到了用户
		if (is_course_find)
		{
			break;
		}
		else
		{
			std::cout << "没有找到该用户，请重新输入" << std::endl;
		}
	}
}

// 查看课程信息
void ManagerModuleTools::Manage_CheckCourseData(const CourseData& cData)
{
	const Course* p_ctemp = NULL;

	while (true)
	{
		// 是查看全部还是查看个别
		std::cout << "A - 查看全部" << std::endl;
		std::cout << "B - 查看单个" << std::endl;
		char a = std::cin.get();
		std::cin.get();
		if (a == 'A' || a == 'a')
		{
			for (size_t i = 0; i < cData.data.size(); i++)
			{
				std::cout << cData.data[i].GetCourseNum()
					<< " "
					<< cData.data[i].GetCourseName()
					<< " "
					<< cData.data[i].GetCourseCredit()
					<< " "
					<< cData.data[i].GetCourseLimit()
					<< " "
					<< cData.data[i].GetCoursePop()
					<< " "
					<< cData.data[i].GetTeacherName()
					<< std::endl;
			}
			break;
		}
		else if (a == 'B' || a == 'b')
		{
			std::cout << "请输入想要查找的课程编号：" << std::endl;
			std::string courseNum;
			std::cin >> courseNum;
			std::cin.get();
			bool is_course_find = false;
			// 找到课程数据
			for (size_t i = 0; i < cData.data.size(); i++)
			{
				if (courseNum == cData.data[i].GetCourseNum())
				{
					is_course_find = true;
					p_ctemp = &(cData.data[i]);
					break;
				}
			}

			std::cout << "课程编号：" << p_ctemp->GetCourseNum()
				<< std::endl
				<< "课程名称：" << p_ctemp->GetCourseName()
				<< std::endl
				<< "学分：" << p_ctemp->GetCourseCredit()
				<< std::endl
				<< "人数上限：" << p_ctemp->GetCourseLimit()
				<< std::endl
				<< "已选人数：" << p_ctemp->GetCoursePop()
				<< std::endl
				<< "教师名称：" << p_ctemp->GetTeacherName()
				<< std::endl;
			break;
		}
		else
		{
			std::cout << "请输入正确字符！" << std::endl;
		}
	}
}

// 查看选课信息
void ManagerModuleTools::Manage_CheckStudentCourseData(const StudentCourseData& scData)
{
	while(true)
	{
		std::cout << "你想进行那种查询？" << std::endl;
		std::cout << "A - 按照课程查询所有学生" << std::endl;
		std::cout << "B - 按照学生查询所有选课" << std::endl;
		char a = std::cin.get();
		std::cin.get();

		if (a == 'A' || a == 'a')
		{
			// 按照课程查询所有学生
			std::cout << "请输入课程编号：" << std::endl;
			std::string courseNum;
			std::cin >> courseNum;
			std::cin.get();
			// 临时存储所有已选该课程的学生信息
			std::vector<StudentCourse> scTempData;
			for (size_t i = 0; i < scData.data.size(); i++)
			{
				// 该学生有选课
				if (scData.data[i].GetSelectedCourseNum() > 0)
				{
					for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
					{
						// 如果说找到了该课程
						if (scData.data[i].selectedCourses[i].GetCourseNum() == courseNum)
						{
							scTempData.push_back(scData.data[i]);
							break;
						}
					}
				}
			}
			// 输出所有找到的学生信息
			std::cout << "选择了该课程的学生有：" << std::endl;
			if (scTempData.size() == 0)
			{
				std::cout << "目前还无人选择该课程" << std::endl;
			}
			else
			{
				for (size_t i = 0; i < scTempData.size(); i++)
				{
					std::cout << scTempData[i].GetID()
						<< " "
						<< scTempData[i].GetName()
						<< std::endl;
				}
			}
			break;
		}
		else if (a == 'B' || a == 'b')
		{
			// 按照学生查询所有选课
			std::cout << "请输入学号：" << std::endl;
			std::string stuID;
			std::cin >> stuID;
			std::cin.get();

			// 查找到该学生的学生选课数据
			for (size_t i = 0; i < scData.data.size(); i++)
			{
				if (scData.data[i].GetID() == stuID)
				{
					std::cout << scData.data[i].GetID() << " " << scData.data[i].GetName()
						<< " "
						<< "已选择的课程有："
						<< std::endl;
					if (scData.data[i].selectedCourses.size() == 0)
					{
						std::cout << "该同学还未进行任何选课" << std::endl;
					}
					else
					{
						for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
						{
							std::cout << scData.data[i].selectedCourses[i].GetCourseNum() << " " << scData.data[i].selectedCourses[i].GetCourseName() << std::endl;
						}
					}
				}
			}
			break;
		}
		else
		{
			std::cout << "请输入正确字符！" << std::endl;
		}
	}
}


/*-------------------------------程序逻辑组--------------------------------*/
// 登录身份判定
bool Log()
{
	std::cout << "欢迎使用学生系统！" << std::endl;
	std::cout << "请根据您的身份输入‘A’或‘B’：" << std::endl;
	std::cout << "A - 我是学生" << std::endl;
	std::cout << "B - 我是管理员" << std::endl;
	// 选择身份
	while (true)
	{
		char a = std::cin.get();
		if (a == 'A' || a == 'a')
		{
			return 1;
		}
		else if (a == 'B' || a == 'b')
		{
			return 0;
		}
		else
		{
			std::cout << "请输入正确的字符" << std::endl;
			std::cin.get();
		}
	}
}

// 登录系统
bool Register(const StudentData & sData, const ManagerData & mData, const User*(* user))
{ 
	//根据选择结果来调用相应的登录系统模块
	bool isStudent = Log();
	if (isStudent)
	{
		// 传递登录时填写的用户信息
		*user = StudentRegister(sData);
	}
	else
	{
		// 传递登录时填写的用户信息
		*user = ManagerRegister(mData);
	}

	return isStudent;
}

// 学生登录模块
const Student* StudentRegister(const StudentData & data)
{
	std::cout << "你好， 请输入学号：" << std::endl;
	std::string stuID;  //用于临时存储学号信息
	std::cin >> stuID;
	const Student* temp;

	// 查找该学生
	temp = FindStudent(stuID, data);

	std::cout << "请输入登录密码：" << std::endl;
	while (true)
	{
		std::string password;
		std::cin >> password;
		std::cin.get();
		// 验证密码
		if (Verification(*temp, password))
		{
			std::cout << "欢迎进入学生系统！" << std::endl;
			break;
		}
		else
		{
			std::cout << "密码错误，请重新输入" << std::endl;
		}
	}

	return temp;
}

// 管理员登录模块
const Manager* ManagerRegister(const ManagerData& data)
{
	const Manager* temp;
	std::cout << "您好，请输入用户名：" << std::endl;
	// 查找该管理员
	temp = FindManager(data);

	std::cout << "请输入密码" << std::endl;
	while (true)
	{
		std::string password;
		std::cin >> password;
		std::cin.get();
		// 验证密码
		if (Verification(data, password))
		{
			std::cout << "欢迎进入管理员系统！" << std::endl;
			break;
		}
		else
		{
			std::cout << "密码错误，请重新输入" << std::endl;
		}
	}

	return temp;
}

// 验证学生密码
bool Verification(const Student & user, const std::string password)
{
	if (user.GetPassword() == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 验证管理员密码
bool Verification(const ManagerData & data, const std::string password)
{
	std::vector<std::string> passwords;
	
	auto end= data.data.end();
	for (auto i = data.data.begin(); i < end; i++)
	{
		if (i->GetPassword() == password)
		{
			return true;
		}
	}
	return false;
}

// 查找学生是否存在
const Student* FindStudent(const std::string temp, const StudentData& data)
{
	// 用于返回值
	const Student* stemp = NULL;

	while (true)
	{
		bool is_find = false;
		auto end = data.data.end();
		for (auto i = data.data.begin(); i < end; i++)
		{
			if (i->GetID() == temp)
			{
				stemp = &(*i);
				is_find = true;
				std::cout << "你好 " + i->GetName() << std::endl;
				break;
			}
		}
		if (is_find)
		{
			return stemp;
		}
		else
		{
			std::cout << "没有找到该用户，请重新输入" << std::endl;
		}
	}
}

// 查找管理员是否存在
const Manager* FindManager(const ManagerData& data)
{
	const Manager* mtemp = NULL;
	while (true)
	{
		std::string temp;
		std::cin >> temp;
		bool is_find = false;
		auto end = data.data.end();
		for (auto i = data.data.begin(); i < end; i++)
		{
			if (i->GetName() == temp)
			{
				mtemp = &(*i);
				is_find = true;
				std::cout << "你好 " + i->GetName() << std::endl;
				break;
			}
		}
		if (is_find)
		{
			return mtemp;
		}
		else
		{
			std::cout << "没有找到该管理员，请重新输入" << std::endl;
		}
	}

}

// 学生系统选项
void StudentSystem(StudentModuleTools tools, CourseData& cData, StudentCourseData& scData, Student s)
{
	while (true)
	{
		std::cout << "请选择你接下来的操作：" << std::endl;
		std::cout << "A - 查看备选课程信息" << std::endl;
		std::cout << "B - 按照课程编号选课" << std::endl;
		std::cout << "C - 查看已选课程信息和累计学分" << std::endl;
		std::cout << "D - 退出系统" << std::endl;
		char a = std::cin.get();
		std::cin.get();
		if (a == 'A' || a == 'a')
		{
			tools.CheckOptionalCourses(cData);
		}
		else if (a == 'B' || a == 'b')
		{
			tools.SelectCourse(cData, scData, s);
		}
		else if (a == 'C' || a == 'c')
		{
			tools.CheckSelected_n_totalCred(scData, s);
		}
		else if (a == 'D' || a == 'd')
		{
			break;
		}
		else
		{
			std::cout << "请输入正确的字符" << std::endl;
		}
		std::cout << std::endl;
	}
}

// 管理员系统选项
void ManagerSystem(ManagerModuleTools tools, StudentData& sData, ManagerData& mData, CourseData& cData, StudentCourseData& scData, Manager m)
{
	while (true)
	{

		std::cout << "请选择你接下来的操作：" << std::endl;
		std::cout << "A - 增加数据" << std::endl;
		std::cout << "B - 删除数据" << std::endl;
		std::cout << "C - 修改数据" << std::endl;
		std::cout << "D - 查看数据" << std::endl;
		std::cout << "E - 退出" << std::endl;
		char a = std::cin.get();
		std::cin.get();
		if (a == 'A' || a == 'a')
		{
			// 增加数据
			while (true)
			{
				std::cout << "请选择你接下来的操作：" << std::endl;
				std::cout << "A - 增加学生数据" << std::endl;
				std::cout << "B - 增加课程数据" << std::endl;
				std::cout << "C - 返回上一步" << std::endl;
				char a = std::cin.get();
				std::cin.get();
				if (a == 'A' || a == 'a')
				{
					tools.Manage_Add(sData, scData);
				}
				else if (a == 'B' || a == 'b')
				{
					tools.Manage_Add(cData);
				}
				else if (a == 'C' || a == 'c')
				{
					break;
				}
				else
				{
					std::cout << "请输入正确的字符" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'B' || a == 'b')
		{
			// 删除数据
			while (true)
			{
				std::cout << "请选择你接下来的操作：" << std::endl;
				std::cout << "A - 删除学生数据" << std::endl;
				std::cout << "B - 删除课程数据" << std::endl;
				std::cout << "C - 返回上一步" << std::endl;
				char a = std::cin.get();
				std::cin.get();
				if (a == 'A' || a == 'a')
				{
					tools.Manage_Delete(sData, scData, cData);
				}
				else if (a == 'B' || a == 'b')
				{
					tools.Manage_Delete(cData, scData);
				}
				else if (a == 'C' || a == 'c')
				{
					break;
				}
				else
				{
					std::cout << "请输入正确的字符" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'C' || a == 'c')
		{
			// 修改数据
			while (true)
			{
				std::cout << "请选择你接下来的操作：" << std::endl;
				std::cout << "A - 修改学生数据" << std::endl;
				std::cout << "B - 修改课程数据" << std::endl;
				std::cout << "C - 返回上一步" << std::endl;
				char a = std::cin.get();
				std::cin.get();
				if (a == 'A' || a == 'a')
				{
					tools.Manage_Change(sData, cData, scData);
				}
				else if (a == 'B' || a == 'b')
				{
					tools.Manage_Change(cData, scData);
				}
				else if (a == 'C' || a == 'c')
				{
					break;
				}
				else
				{
					std::cout << "请输入正确的字符" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'D' || a == 'd')
		{
			// 查看数据
			while (true)
			{
				std::cout << "请选择你接下来的操作：" << std::endl;
				std::cout << "A - 查看学生数据" << std::endl;
				std::cout << "B - 查看课程数据" << std::endl;
				std::cout << "C - 查看学生选课数据" << std::endl;
				std::cout << "D - 返回上一步" << std::endl;
				char a = std::cin.get();
				std::cin.get();
				if (a == 'A' || a == 'a')
				{
					tools.Manage_CheckStudentData(sData);
				}
				else if (a == 'B' || a == 'b')
				{
					tools.Manage_CheckCourseData(cData);
				}
				else if (a == 'C' || a == 'c')
				{
					tools.Manage_CheckStudentCourseData(scData);
				}
				else if (a == 'D' || a == 'd')
				{
					break;
				}
				else
				{
					std::cout << "请输入正确的字符" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'E' || a == 'e')
		{
			break;
		}
		else
		{
			std::cout << "请输入正确的字符" << std::endl;
		}
		std::cout << std::endl;
	}
}