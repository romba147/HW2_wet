//
// Created by Eyal on 02/06/2022.
//

#ifndef HW2_WET_UF_H
#define HW2_WET_UF_H


class UF {
    int num; ///not accessed
    int* sizes;
    int* id;
    int* alias;
    double* bumps;
    double* values;
    int groupsNum;
public:
    explicit UF(int size)
    {
        this->num = size;
        this->groupsNum = size;
        sizes = new int[size+1];
        id = new int[size+1];
        values = new double[size+1];
        alias = new int[size+1];
        bumps = new double [size+1];

        for (int i=0 ; i<(long int)size+1 ; i++) ///omer: changed to long int (max int input)
        {
            id[i] = i;
            sizes[i] = 1;
            alias[i] = i;
            values[i] = i;
            bumps[i] = 0;
        }
    }

    ~UF()
    {
        delete[] id;
        delete[] sizes;
        delete[] values;
        delete[] bumps;
        delete[] alias;
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
            return root;
        }
        int to_return = findAux(id[root], sumBumps);
        *(sumBumps) += bumps[root];
        bumps[root] = *(sumBumps);
        id[root] = to_return;
        return to_return;
    }

    int getAlias(int n)
    {
        int to_return = find(n);
        return alias[to_return];
    }


    void merge(int g1 , int g2, double factor)
    {
        //root1 acquire root2
        //B is placed on A
        //root1 == B, root2 == A
        int root1 = find(g1);
        int root2 = find(g2);
        if (root2 == root1)
        {
            return;
        }
        if (sizes[root1] >= sizes[root2]) {
            id[root2] = id[root1];
            sizes[root1] = sizes[root1] + sizes[root2];
            bumps[root1] += factor * (values[root2]);
            values[root1] += factor * (values[root2]);
            bumps[root2] -= bumps[root1];
            values[root2] = 0;
            alias[root2] = 0;
        }
        else {
            id[root1] = id[root2];
            bumps[root1] += factor*(values[root2]);
            sizes[root2] = sizes[root2] + sizes[root1];
            values[root2] = values[root1] + factor*(values[root2]);
            bumps[root1] -= bumps[root2];
            alias[root2] = alias[root1];
            alias[root1] = 0;
        }
        groupsNum--;
    }
    int getGroupsNum() const
    {
        return groupsNum;
    }
    int getGroupSize(int group)
    {
        int root = find(group);
        return sizes[root];
    }
    double getValue(int n)
    {
        double to_return = 0;
        auto sum = new double (0);
        int current_company = findAux(n , sum);
        to_return =(double)n+*(sum) + bumps[current_company];
        delete sum;
        return to_return;
    }

};


#endif //HW2_WET_UF_H
