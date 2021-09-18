#include <stdio.h>
#include "Hanoi.hpp"
std::vector<disk> disks;
void draw_disks();
std::vector<disk> get_disks_by_index(int index) {
	std::vector<disk> result;
	for (auto _disk : disks) {
		if (_disk.x == index) result.push_back(_disk);
	}
	return result;
}
int get_proper_height(int index) {
	int result = 0;
	for (auto _disk : disks) {
		if (_disk.x == index) result++;
	}
	return result;
}
int get_sum_proper_height(int index) {
	int height = get_proper_height(index);
	int result = 0;
	while (height >= 1) {
		result += height;
		height--;
	}
	return result;
}
void gravity(int index) { //�߷�
	for (auto& _disk : disks) {
		if (_disk.x == index) {
			_disk.y--;
		}
	}
}
int get_sum_y(int index) {
	int result = 0;
	for (auto _disk : disks) {
		if (_disk.x == index) result += _disk.y;
	}
	return result;
}
bool is_aligned(int index) { //��: ���� ������ �����κ��� ���������� �ʴٸ� get_sum_y�� ���� ���� ���� Ư�� ��ǥ�� y�� ���հ� get_sum_proper_height�� ���� ���� �ùٸ� ���̵��� ������ ���� ���̴�.
	return get_sum_y(index) == get_sum_proper_height(index);
}
bool get_highest_width(int index, int& width) {
	std::vector<disk> _disk = get_disks_by_index(index);

	if (_disk.size() > 0) {
		std::sort(_disk.begin(), _disk.end(), [](disk const& a, disk const& b)
			{
				return a.w < b.w;
			});
		width = _disk.front().w;
		return true;
	}
	return false;
}
void vertical_align_disks() {
	int count = 99;
	for (auto& _disk : disks) {
		if (!is_aligned(_disk.x)) { //�������� �ϱ� ���� �����غ�..
			_disk.y = count;
			count--;
		}
	}

	for (auto& _disk : disks) {
		while (!is_aligned(_disk.x)) { //�������ĵǾ� ���� ���� ��� ���ĵ� ������ �߷��Լ��� ȣ����. 
			gravity(_disk.x);

		}
	}
}
bool is_able_to_move(disk payload, int index) {
	int current_width;
	if (get_highest_width(payload.x, current_width)) { // ���� target�� Ÿ���� ���� ������ ��ġ�ϰ� �ִٸ� get_highest_width�Լ��� ���ϰ�(current_width)�� payload.w�� ���� ���̴�.
		if (payload.w == current_width) {
;
			//���⼭���� "�ϴ�" �ű� �� �ִ�.
			int current_target_width;
			if (!get_highest_width(index, current_width)) return true;
			if (payload.w < current_width) return true;

		}
	}
	return false;
}
bool move_payload(disk payload, int index) {

	if (!is_able_to_move(payload, index)) {

		return false;
	}
	for (auto& _disk : disks) {
		if (_disk.w == payload.w) {
			_disk.x = index;
			vertical_align_disks();
			while (!is_aligned(_disk.x)) { //�������ĵǾ� ���� ���� ��� ���ĵ� ������ �߷��Լ��� ȣ����. 
				gravity(_disk.x);
				
			}

		}
	}
	return true;
}
bool get_highest_disk(int index,  disk &payload) {
	vertical_align_disks();
	std::vector<disk> _disk = get_disks_by_index(index);

	if (_disk.size() > 0) {
		std::sort(_disk.begin(), _disk.end(), [](disk const& a, disk const& b)
			{
				return a.w < b.w;
			});
		payload = _disk.front();
		return true;
	}
	return false;
}
bool move_payload_wrapper(int from, int to) {
	disk payload;
	if (get_highest_disk(from, payload)) {
		return move_payload(payload,to);
	}
	return false;
}
void hanoi(int disks, int from, int temp, int to)
{
	if (disks == 1)
	{
		move_payload_wrapper(from, to);
		draw_disks();
	}
	else
	{
		hanoi(disks - 1, from, to, temp);
		move_payload_wrapper(from, to);
		draw_disks();
		hanoi(disks - 1, temp, from, to);
	}
}


void draw_disks()
{
	vertical_align_disks();
	std::vector<disk> tower1 = get_disks_by_index(1);
	std::vector<disk> tower2 = get_disks_by_index(2);
	std::vector<disk> tower3 = get_disks_by_index(3);

	std::sort(tower1.begin(), tower1.end(), [](disk const& a, disk const& b)
		{
			return a.w < b.w;
		});
	std::sort(tower2.begin(), tower2.end(), [](disk const& a, disk const& b)
		{
			return a.w < b.w;
		});
	std::sort(tower3.begin(), tower3.end(), [](disk const& a, disk const& b)
		{
			return a.w < b.w;
		});

	for (int i = 4; i >= 1; i--) {
		for (auto _disk : tower1) {
			if (_disk.y == i) {
				for (int j = 0; j < _disk.w; j++)
					printf("��");
			}
		}
		printf("\t\t");
		for (auto _disk : tower2) {
			if (_disk.y == i) {
				for (int j = 0; j < _disk.w; j++)
					printf("��");
			}
		}
		printf("\t\t");
		for (auto _disk : tower3) {
			if (_disk.y == i) {
				for (int j = 0; j < _disk.w; j++)
					printf("��");
			}
		}
		printf("\n");

	}
	printf("����������������������\t����������������������\t����������������������\n\n\n");
}
int main()
{
	disks.push_back(disk{ 1, 4, 1 });
	disks.push_back(disk{ 1, 3, 2 });
	disks.push_back(disk{ 1, 2, 3 });
	disks.push_back(disk{ 1, 1, 4 });
	draw_disks();
	hanoi(4, 1, 2, 3);

}
