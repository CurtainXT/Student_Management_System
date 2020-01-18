#include"StuManage.h"

/*-------------------------------ѧ��������--------------------------------*/
// �鿴��ѡ�γ���Ϣ
void StudentModuleTools::CheckOptionalCourses(const CourseData& data)
{
	// ���ڱ������п���ѡ��Ŀγ���Ϣ
	CourseData temp;
	for (size_t i = 0; i < data.data.size(); i++)
	{
		if (!data.data[i].isFull())
		{
			temp.data.push_back(data.data[i]);
		}
	}
	std::cout << std::endl;
	std::cout << "����ѡ��Ŀγ��У�" << std::endl;
	// ��ӡ���п�ѡ�γ���Ϣ
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

// ���տγ̱��ѡ��
void StudentModuleTools::SelectCourse(CourseData& cData, StudentCourseData& scData, const Student& user) 
{
	std::cout << std::endl;
	std::cout << "������γ̱��" << std::endl;
	std::string courseNumTemp;
	std::cin >> courseNumTemp;
	std::cin.get();

	for (size_t i = 0; i < cData.data.size(); i++)
	{
		// ���Ҹÿγ̱��
		if (cData.data[i].GetCourseNum() == courseNumTemp)
		{
			// ��֤�ÿγ��Ƿ�����
			if(!cData.data[i].isFull())
			{ 
				// ���ҵ����û���ѧ��ѡ������
				StudentCourse* user_sc = NULL;
				for (size_t c = 0; c < scData.data.size(); c++)
				{
					if (scData.data[c].GetID() == user.GetID())
					{
						// ����ҵ��ˣ��������
						user_sc = &(scData.data[c]);
					}
				}

				// ���ѡ���Ƿ��ظ�
				bool isSelected = false;
				for (size_t i = 0; i < user_sc->selectedCourses.size(); i++)
				{
					// ���Ҫѡ��Ŀγ��Ѿ���ѡ��
					if (courseNumTemp == (*user_sc).selectedCourses[i].GetCourseNum())
					{
						isSelected = true;
					}
				}
				// ���û���ظ�
				if (!isSelected)
				{
					std::cout << "��ѡ��γ̣�" << std::endl;
					std::cout << cData.data[i].GetCourseNum()
						<< " "
						<< cData.data[i].GetCourseName()
						<< std::endl;
					// ���γ̵���ѡ������һ
					cData.data[i].AddOnePopulation();
					// ��ѧ��ѡ�ε���ѡ������һ
					user_sc->AddOneSeletedCourseNum();
					// ��ѧ���γ���������Ӹ�ѡ����Ϣ
					user_sc->selectedCourses.push_back(cData.data[i]);
				}
				else
				{
					std::cout << "�ÿγ��Ѿ���ѡ�����" << std::endl;
					break;
				}
			}
			else
			{
				std::cout << "�ÿγ�����" << std::endl;
				break;
			}
		}
	}
}

// �鿴��ѡ�γ���Ϣ���ۼ�ѧ��
void StudentModuleTools::CheckSelected_n_totalCred(const StudentCourseData& scData, const Student& user)
{
	// ���ҵ����û���ѧ��ѡ������
	const StudentCourse* user_sc = NULL;
	for (size_t c = 0; c < scData.data.size(); c++)
	{
		if (scData.data[c].GetID() == user.GetID())
		{
			// ����ҵ��ˣ��������
			user_sc = &(scData.data[c]);
		}
	}
	if (user_sc == NULL)
	{
		std::cout << "δ�ҵ���ѧ����ѡ����Ϣ��" << std::endl;
		return;
	}
	else
	{
		std::cout << "�����ѡ�γ��У�" << std::endl;
		if (user_sc->selectedCourses.size() == 0)
		{
			std::cout << "�㻹û�н����κ�ѡ�Σ�" << std::endl;
		}
		else
		{
			for (size_t i = 0; i < user_sc->selectedCourses.size(); i++)
			{
				std::cout << user_sc->selectedCourses[i].GetCourseNum() << " "
					<< user_sc->selectedCourses[i].GetCourseName() << std::endl;
			}
			std::cout << "�ܹ�ѧ��Ϊ��" << user_sc->GetTotalCredits() << std::endl;
		}
	}
}

/*-------------------------------����Ա������--------------------------------*/
// ����ѧ����Ϣ
void ManagerModuleTools::Manage_Add(StudentData& sData, StudentCourseData& scData)
{
	// ���û���ȡ��Ϣ
	std::cout << "������Ҫ��ӵ�ѧ����Ϣ��" << std::endl;
	std::string data1;
	std::string data2;
	std::string data3;
	std::string data4;
	std::string data5;
	std::cout << "������רҵ��";
	std::cin >> data1;
	std::cout << "������༶��";
	std::cin >> data2;
	std::cout << "������ѧ�ţ�";
	std::cin >> data3;
	std::cout << "������������";
	std::cin >> data4;
	std::cout << "�������¼���룺";
	std::cin >> data5;
	std::cin.get();

	// ����õ���Ϣ���ڹ����µ����ݶ���
	Student stemp(data1, data2, data3, data4, data5);
	StudentCourse sctemp(data1, data2, data3, data4);

	// ����������ӵ�����������
	sData.data.push_back(stemp);
	scData.data.push_back(sctemp);
	std::cout << "��ӳɹ�!" << std::endl;
}

// ɾ��ѧ����Ϣ
void ManagerModuleTools::Manage_Delete(StudentData& sData, StudentCourseData& scData, CourseData& cData)
{
	while (true)
	{
		std::string stuID;
		std::cout << "������Ҫɾ��ѧ����ѧ�ţ�" << std::endl;
		std::cin >> stuID;
		std::cin.get();

		bool is_stu_success = false;
		bool is_sc_success = false;
		
		for (size_t i = 0; i < sData.data.size(); i++)
		{
			if (sData.data[i].GetID() == stuID)
			{
				// ɾ��ѧ������
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
				// �洢�κ�
				std::vector<std::string> courseNums;
				// ɾ��֮ǰ�޸�����ѡ�γ̵�ѡ����������
				for (int c = 0; c < scData.data[i].GetSelectedCourseNum(); c++)
				{
					//�õ�������ѡ�εĿκ�
					courseNums.push_back(scData.data[i].selectedCourses[c].GetCourseNum());
				}
				for (size_t r = 0; r < courseNums.size(); r++)
				{
					// ���γ̵���ѡ������һ
					for (size_t d = 0; d < cData.data.size(); d++)
					{
						if (courseNums[r] == cData.data[d].GetCourseNum())
						{
							cData.data[d].MinusOnePopulation();
							break;
						}
					}
				}

				// ɾ��ѧ��ѡ������
				auto iter = scData.data.begin() + i;
				scData.data.erase(iter);
				is_sc_success = true;
				break;
			}
		}

		if (is_stu_success && is_sc_success)
		{
			std::cout << "�ɹ�ɾ��ѧ����Ϣ��" << std::endl;
			break;
		}
		else
		{
			std::cout << "δ�ҵ���ѧ����Ϣ������������!" << std::endl;
		}
	}
}

// �޸�ѧ����Ϣ
void ManagerModuleTools::Manage_Change(StudentData& sData, CourseData& cData, StudentCourseData& scData)
{
	// �ҵ����û�
	Student* p_stemp = NULL;
	StudentCourse* p_sctemp = NULL;

	while (true)
	{
		std::cout << "��������Ҫ�޸ĵ�ѧ����ѧ��" << std::endl;
		std::string stuID;
		std::cin >> stuID;
		std::cin.get();
		bool is_stu_find = false;
		bool is_sc_find = false;
		// �ҵ�ѧ������
		for (size_t i = 0; i < sData.data.size(); i++)
		{
			if (stuID == sData.data[i].GetID())
			{
				is_stu_find = true;
				p_stemp = &(sData.data[i]);
				break;
			}
		}
		// �ҵ�ѧ��ѡ������
		for (size_t i = 0; i < scData.data.size(); i++)
		{
			if (stuID == scData.data[i].GetID())
			{
				is_sc_find = true;
				p_sctemp = &(scData.data[i]);

				// �޸�����֮ǰ���Ƚ�ԭ���ݵ�ѡ�μ�¼ɾ��
				std::vector<std::string> courseNums; // �洢�κ�
				// ɾ��֮ǰ�޸�����ѡ�γ̵�ѡ����������
				for (int c = 0; c < p_sctemp->GetSelectedCourseNum(); c++)
				{
					//�õ�������ѡ�εĿκ�
					courseNums.push_back(scData.data[i].selectedCourses[c].GetCourseNum());
				}
				for (size_t r = 0; r < courseNums.size(); r++)
				{
					// ���γ̵���ѡ������һ
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
		// ȷ���Ƿ��ҵ����û�
		if (is_stu_find && is_sc_find)
		{
			break;
		}
		else
		{
			std::cout << "û���ҵ����û�������������" << std::endl;
		}
	}

	std::cout << "�������޸��Ժ������" << std::endl;
	std::string data1;
	std::string data2;
	std::string data3;
	std::string data4;
	std::string data5;
	std::cout << "������רҵ��";
	std::cin >> data1;
	std::cout << "������༶��";
	std::cin >> data2;
	std::cout << "������ѧ�ţ�";
	std::cin >> data3;
	std::cout << "������������";
	std::cin >> data4;
	std::cout << "�������¼���룺";
	std::cin >> data5;
	std::cout << "�޸ĳɹ���" << std::endl;
	Student stemp(data1, data2, data3, data4, data5);
	StudentCourse sctemp(data1, data2, data3, data4);
	*p_stemp = stemp;
	*p_sctemp = sctemp;
}

// ����ѧ����Ϣ
void ManagerModuleTools::Manage_CheckStudentData(const StudentData& sData)
{
	while (true)
	{
		// �ǲ鿴ȫ�����ǲ鿴����
		std::cout << "A - �鿴ȫ��" << std::endl;
		std::cout << "B - �鿴����" << std::endl;
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
			std::cout << "������Ҫ���ҵ�ѧ��ѧ��" << std::endl;
			std::string stuID;
			std::cin >> stuID;
			std::cin.get();

			// �ҵ����û�
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
					std::cout << "û���ҵ����û�������������" << std::endl;
				}
			}

			std::cout << "רҵ��" << p_temp->GetMajor()
				<< std::endl
				<< "�༶��" << p_temp->GetClassNum()
				<< std::endl
				<< "ѧ�ţ�" << p_temp->GetID()
				<< std::endl
				<< "������" << p_temp->GetName()
				<< std::endl
				<< "��¼���룺" << p_temp->GetPassword();

			break;
		}
		else
		{
			std::cout << "��������ȷ�ַ���" << std::endl;
		}
	}
}

// ���ӿγ���Ϣ
void ManagerModuleTools::Manage_Add(CourseData& cData)
{
	std::string data1;
	std::string data2;
	int data3;
	int data4;
	int data5 = 0;
	std::string data6;
	std::cout << "�����¿γ̿κ�" << std::endl;;
	std::cin >> data1;
	std::cout << "�����¿γ�����" << std::endl;
	std::cin >> data2;
	std::cout << "�����¿γ�ѧ��" << std::endl;
	std::cin >> data3;
	std::cout << "�����¿γ���������" << std::endl;
	std::cin >> data4;
	std::cout << "�����¿γ��ڿ���ʦ" << std::endl;
	std::cin >> data6;
	std::cin.get();
	cData.data.push_back(Course(data1, data2, data3, data4, data5, data6));
	std::cout << "��ӳɹ���" << std::endl;
}

//// ɾ���γ���Ϣ
void ManagerModuleTools::Manage_Delete(CourseData& cData, StudentCourseData& scData)
{
	std::cout << "����Ҫɾ���γ̵Ŀγ̺�" << std::endl;
	std::string courseNum;
	std::cin >> courseNum;
	std::cin.get();

	// ɾ������ѧ��ѡ���б��γ̵ļ�¼
	for (size_t i = 0; i < scData.data.size(); i++)
	{
		// �����ѧ��ѡ�˿�
		if (scData.data[i].GetSelectedCourseNum() > 0)
		{
			// ���������Ƿ��иÿγ�
			for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
			{
				// ����У�ɾ��ѡ�μ�¼
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
	// �ڿγ������������ҵ��ÿγ�
	for (size_t i = 0; i < cData.data.size(); i++)
	{
		if (courseNum == cData.data[i].GetCourseNum())
		{
			// ɾ����
			auto iter = cData.data.begin() + i;
			cData.data.erase(iter);
			break;
		}
	}
	std::cout << "ɾ���ɹ���" << std::endl;
}

// �޸Ŀγ���Ϣ
void ManagerModuleTools::Manage_Change(CourseData& cData, StudentCourseData& scData)
{
	// �ҵ��ÿγ�
	Course* p_ctemp = NULL;

	while (true)
	{
		std::cout << "��������Ҫ�޸ĵĿγ̱�ţ�" << std::endl;
		std::string courseNum;
		std::cin >> courseNum;
		std::cin.get();
		bool is_course_find = false;
		// �ҵ��γ�����
		for (size_t i = 0; i < cData.data.size(); i++)
		{
			if (courseNum == cData.data[i].GetCourseNum())
			{
				is_course_find = true;
				p_ctemp = &(cData.data[i]);
				break;
			}
		}

		// �޸Ŀγ���Ϣ
		std::string data1;
		int data2;
		bool is_find = false;
		do
		{
			std::cout << "ѡ��Ҫ�޸ĵĿγ���Ϣ" << std::endl;
			std::cout << "A - �γ̱��" << std::endl;
			std::cout << "B - �γ�����" << std::endl;
			std::cout << "C - ѧ��" << std::endl;
			std::cout << "D - �ڿ���ʦ" << std::endl;

			char a = std::cin.get();
			std::cin.get();
			switch (a)
			{
			case 'A':
			case 'a':
				std::cout << "�������µĿγ̱��" << std::endl;
				std::cin >> data1;
				std::cin.get();
				p_ctemp->SetCourseNum(data1);
				is_find = true;
				break;
			case 'B':
			case 'b':
				std::cout << "�������µĿγ�����" << std::endl;
				std::cin >> data1;
				std::cin.get();
				p_ctemp->SetTeacherName(data1);
				is_find = true;
				break;
			case 'C':
			case 'c':
				std::cout << "�������µ�ѧ��" << std::endl;
				std::cin >> data2;
				std::cin.get();
				p_ctemp->SetCourseCredit(data2);
				is_find = true;
				break;
			case 'D':
			case 'd':
				std::cout << "�������µ��ڿ���ʦ" << std::endl;
				std::cin >> data1;
				std::cin.get();
				p_ctemp->SetTeacherName(data1);
				is_find = true;
				break;
			default:
				std::cout << "��������ȷ�ַ�";
				break;
			}
		} while (!is_find);

		// �ҵ�ѧ��ѡ�������е����б��γ�
		for (size_t i = 0; i < scData.data.size(); i++)
		{
			// ��ѧ����ѡ��
			if (scData.data[i].GetSelectedCourseNum() > 0)
			{
				// �����Ƿ�ѡ�˸ÿγ�
				for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
				{
					// ���ѡ��
					if (scData.data[i].selectedCourses[c].GetCourseNum() == courseNum)
					{
						// ���¿γ����ݵ��޸�
						scData.data[i].selectedCourses[c] = Course(p_ctemp->GetCourseNum(), p_ctemp->GetCourseName(), p_ctemp->GetCourseCredit(), p_ctemp->GetTeacherName());
						break;
					}
				}
			}
		}
		// ȷ���Ƿ��ҵ����û�
		if (is_course_find)
		{
			break;
		}
		else
		{
			std::cout << "û���ҵ����û�������������" << std::endl;
		}
	}
}

// �鿴�γ���Ϣ
void ManagerModuleTools::Manage_CheckCourseData(const CourseData& cData)
{
	const Course* p_ctemp = NULL;

	while (true)
	{
		// �ǲ鿴ȫ�����ǲ鿴����
		std::cout << "A - �鿴ȫ��" << std::endl;
		std::cout << "B - �鿴����" << std::endl;
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
			std::cout << "��������Ҫ���ҵĿγ̱�ţ�" << std::endl;
			std::string courseNum;
			std::cin >> courseNum;
			std::cin.get();
			bool is_course_find = false;
			// �ҵ��γ�����
			for (size_t i = 0; i < cData.data.size(); i++)
			{
				if (courseNum == cData.data[i].GetCourseNum())
				{
					is_course_find = true;
					p_ctemp = &(cData.data[i]);
					break;
				}
			}

			std::cout << "�γ̱�ţ�" << p_ctemp->GetCourseNum()
				<< std::endl
				<< "�γ����ƣ�" << p_ctemp->GetCourseName()
				<< std::endl
				<< "ѧ�֣�" << p_ctemp->GetCourseCredit()
				<< std::endl
				<< "�������ޣ�" << p_ctemp->GetCourseLimit()
				<< std::endl
				<< "��ѡ������" << p_ctemp->GetCoursePop()
				<< std::endl
				<< "��ʦ���ƣ�" << p_ctemp->GetTeacherName()
				<< std::endl;
			break;
		}
		else
		{
			std::cout << "��������ȷ�ַ���" << std::endl;
		}
	}
}

// �鿴ѡ����Ϣ
void ManagerModuleTools::Manage_CheckStudentCourseData(const StudentCourseData& scData)
{
	while(true)
	{
		std::cout << "����������ֲ�ѯ��" << std::endl;
		std::cout << "A - ���տγ̲�ѯ����ѧ��" << std::endl;
		std::cout << "B - ����ѧ����ѯ����ѡ��" << std::endl;
		char a = std::cin.get();
		std::cin.get();

		if (a == 'A' || a == 'a')
		{
			// ���տγ̲�ѯ����ѧ��
			std::cout << "������γ̱�ţ�" << std::endl;
			std::string courseNum;
			std::cin >> courseNum;
			std::cin.get();
			// ��ʱ�洢������ѡ�ÿγ̵�ѧ����Ϣ
			std::vector<StudentCourse> scTempData;
			for (size_t i = 0; i < scData.data.size(); i++)
			{
				// ��ѧ����ѡ��
				if (scData.data[i].GetSelectedCourseNum() > 0)
				{
					for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
					{
						// ���˵�ҵ��˸ÿγ�
						if (scData.data[i].selectedCourses[i].GetCourseNum() == courseNum)
						{
							scTempData.push_back(scData.data[i]);
							break;
						}
					}
				}
			}
			// ��������ҵ���ѧ����Ϣ
			std::cout << "ѡ���˸ÿγ̵�ѧ���У�" << std::endl;
			if (scTempData.size() == 0)
			{
				std::cout << "Ŀǰ������ѡ��ÿγ�" << std::endl;
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
			// ����ѧ����ѯ����ѡ��
			std::cout << "������ѧ�ţ�" << std::endl;
			std::string stuID;
			std::cin >> stuID;
			std::cin.get();

			// ���ҵ���ѧ����ѧ��ѡ������
			for (size_t i = 0; i < scData.data.size(); i++)
			{
				if (scData.data[i].GetID() == stuID)
				{
					std::cout << scData.data[i].GetID() << " " << scData.data[i].GetName()
						<< " "
						<< "��ѡ��Ŀγ��У�"
						<< std::endl;
					if (scData.data[i].selectedCourses.size() == 0)
					{
						std::cout << "��ͬѧ��δ�����κ�ѡ��" << std::endl;
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
			std::cout << "��������ȷ�ַ���" << std::endl;
		}
	}
}


/*-------------------------------�����߼���--------------------------------*/
// ��¼����ж�
bool Log()
{
	std::cout << "��ӭʹ��ѧ��ϵͳ��" << std::endl;
	std::cout << "���������������롮A����B����" << std::endl;
	std::cout << "A - ����ѧ��" << std::endl;
	std::cout << "B - ���ǹ���Ա" << std::endl;
	// ѡ�����
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
			std::cout << "��������ȷ���ַ�" << std::endl;
			std::cin.get();
		}
	}
}

// ��¼ϵͳ
bool Register(const StudentData & sData, const ManagerData & mData, const User*(* user))
{ 
	//����ѡ������������Ӧ�ĵ�¼ϵͳģ��
	bool isStudent = Log();
	if (isStudent)
	{
		// ���ݵ�¼ʱ��д���û���Ϣ
		*user = StudentRegister(sData);
	}
	else
	{
		// ���ݵ�¼ʱ��д���û���Ϣ
		*user = ManagerRegister(mData);
	}

	return isStudent;
}

// ѧ����¼ģ��
const Student* StudentRegister(const StudentData & data)
{
	std::cout << "��ã� ������ѧ�ţ�" << std::endl;
	std::string stuID;  //������ʱ�洢ѧ����Ϣ
	std::cin >> stuID;
	const Student* temp;

	// ���Ҹ�ѧ��
	temp = FindStudent(stuID, data);

	std::cout << "�������¼���룺" << std::endl;
	while (true)
	{
		std::string password;
		std::cin >> password;
		std::cin.get();
		// ��֤����
		if (Verification(*temp, password))
		{
			std::cout << "��ӭ����ѧ��ϵͳ��" << std::endl;
			break;
		}
		else
		{
			std::cout << "�����������������" << std::endl;
		}
	}

	return temp;
}

// ����Ա��¼ģ��
const Manager* ManagerRegister(const ManagerData& data)
{
	const Manager* temp;
	std::cout << "���ã��������û�����" << std::endl;
	// ���Ҹù���Ա
	temp = FindManager(data);

	std::cout << "����������" << std::endl;
	while (true)
	{
		std::string password;
		std::cin >> password;
		std::cin.get();
		// ��֤����
		if (Verification(data, password))
		{
			std::cout << "��ӭ�������Աϵͳ��" << std::endl;
			break;
		}
		else
		{
			std::cout << "�����������������" << std::endl;
		}
	}

	return temp;
}

// ��֤ѧ������
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

// ��֤����Ա����
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

// ����ѧ���Ƿ����
const Student* FindStudent(const std::string temp, const StudentData& data)
{
	// ���ڷ���ֵ
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
				std::cout << "��� " + i->GetName() << std::endl;
				break;
			}
		}
		if (is_find)
		{
			return stemp;
		}
		else
		{
			std::cout << "û���ҵ����û�������������" << std::endl;
		}
	}
}

// ���ҹ���Ա�Ƿ����
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
				std::cout << "��� " + i->GetName() << std::endl;
				break;
			}
		}
		if (is_find)
		{
			return mtemp;
		}
		else
		{
			std::cout << "û���ҵ��ù���Ա������������" << std::endl;
		}
	}

}

// ѧ��ϵͳѡ��
void StudentSystem(StudentModuleTools tools, CourseData& cData, StudentCourseData& scData, Student s)
{
	while (true)
	{
		std::cout << "��ѡ����������Ĳ�����" << std::endl;
		std::cout << "A - �鿴��ѡ�γ���Ϣ" << std::endl;
		std::cout << "B - ���տγ̱��ѡ��" << std::endl;
		std::cout << "C - �鿴��ѡ�γ���Ϣ���ۼ�ѧ��" << std::endl;
		std::cout << "D - �˳�ϵͳ" << std::endl;
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
			std::cout << "��������ȷ���ַ�" << std::endl;
		}
		std::cout << std::endl;
	}
}

// ����Աϵͳѡ��
void ManagerSystem(ManagerModuleTools tools, StudentData& sData, ManagerData& mData, CourseData& cData, StudentCourseData& scData, Manager m)
{
	while (true)
	{

		std::cout << "��ѡ����������Ĳ�����" << std::endl;
		std::cout << "A - ��������" << std::endl;
		std::cout << "B - ɾ������" << std::endl;
		std::cout << "C - �޸�����" << std::endl;
		std::cout << "D - �鿴����" << std::endl;
		std::cout << "E - �˳�" << std::endl;
		char a = std::cin.get();
		std::cin.get();
		if (a == 'A' || a == 'a')
		{
			// ��������
			while (true)
			{
				std::cout << "��ѡ����������Ĳ�����" << std::endl;
				std::cout << "A - ����ѧ������" << std::endl;
				std::cout << "B - ���ӿγ�����" << std::endl;
				std::cout << "C - ������һ��" << std::endl;
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
					std::cout << "��������ȷ���ַ�" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'B' || a == 'b')
		{
			// ɾ������
			while (true)
			{
				std::cout << "��ѡ����������Ĳ�����" << std::endl;
				std::cout << "A - ɾ��ѧ������" << std::endl;
				std::cout << "B - ɾ���γ�����" << std::endl;
				std::cout << "C - ������һ��" << std::endl;
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
					std::cout << "��������ȷ���ַ�" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'C' || a == 'c')
		{
			// �޸�����
			while (true)
			{
				std::cout << "��ѡ����������Ĳ�����" << std::endl;
				std::cout << "A - �޸�ѧ������" << std::endl;
				std::cout << "B - �޸Ŀγ�����" << std::endl;
				std::cout << "C - ������һ��" << std::endl;
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
					std::cout << "��������ȷ���ַ�" << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else if (a == 'D' || a == 'd')
		{
			// �鿴����
			while (true)
			{
				std::cout << "��ѡ����������Ĳ�����" << std::endl;
				std::cout << "A - �鿴ѧ������" << std::endl;
				std::cout << "B - �鿴�γ�����" << std::endl;
				std::cout << "C - �鿴ѧ��ѡ������" << std::endl;
				std::cout << "D - ������һ��" << std::endl;
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
					std::cout << "��������ȷ���ַ�" << std::endl;
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
			std::cout << "��������ȷ���ַ�" << std::endl;
		}
		std::cout << std::endl;
	}
}