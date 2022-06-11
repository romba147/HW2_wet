//
// Created by Eyal on 02/06/2022.
//

#ifndef HW2_WET_UF_H
#define HW2_WET_UF_H


class UF {
    int num;
    int* sizes;
    int* id;
    double* bumps;
    double* values;
    int groupsNum;
public:
    explicit UF(int size)
    {
        this->num = size;
        this->groupsNum = size;
        sizes = new int[size];
        id = new int[size];
        bumps = new double [size];
        values= new double [size];

        for (int i=0 ; i<size ; i++)
        {
            id[i] = i;
            sizes[i] = 1;
            values[i] = double (i);
        }
    }
    ~UF()
    {
        delete id;
        delete sizes;
    }

    int find (int root)
    {
        double sumBumps =0;
        return findAux(root, &sumBumps);
    }

    int findAux (int root ,double *sumBumps)
    {
        if (id[root] == root)
        {
            *(sumBumps) += bumps[root];
            return root;
        }
        int to_return = find(id[root], sumBumps);
        *(sumBumps) += bumps[root];
        bumps[root] = *(sumBumps);
        id[root] = to_return;
        return to_return;
    }


    void merge(int g1 , int g2, double factor)
    {
        auto sumBumps = new double (0);
        int root1 = find(g1,sumBumps);
        *sumBumps=0;
        int root2 = find(g2,sumBumps);
        if (root2 == root1) return;
        if (sizes[root1] > sizes[root2])
        {
            id[root2] = id[root1];
            sizes[root1] = sizes[root1] + sizes[root2];
            bumps[g1] += factor*(values[g2]);
            bumps[g2] -= bumps[g1];
            values[g1] += factor*(values[g2]);
        }
        else
        {
            id[root1] = id[root2];
            sizes[root2] = sizes[root1] + sizes[root2];
            bumps[g2] += factor*(values[g1]);
            bumps[g1] -= bumps[g2];
            values[g2] += factor*(values[g1]);
        }
        groupsNum--;
        delete sumBumps;
    }
    int getGroupsNum() const
    {
        return groupsNum;
    }
    int getGroupSize(int group)
    {
        auto n = new double(0);
        int root = find(group,n);
        delete n;
        return sizes[root];
    }
    double getValue(int n)
    {
        int to_return = 0;
        auto sum = new double (0);
        find(n , sum);
        return values[n] + *(sum);

    }

};


#endif //HW2_WET_UF_H
