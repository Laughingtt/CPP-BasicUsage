//
// Created by tian on 2022/9/21.
//

#ifndef ECDH_ECC_OBLIVIOUS_TRANSFER_H
#define ECDH_ECC_OBLIVIOUS_TRANSFER_H

#include "string"
#include "ecc.h"

/*
* 输入：发送方（以S 代表) 有 n 个消息（m_0,m_1⋯⋯m_n−1），接收方（R )对第 i  个感兴趣。
输出：R 得到了 m_i，但得不到其他的m，S 也不知道 i。

S 方生成私钥a, 计算得到公钥 A=a∙G，将 A 发送给 R 方。
R 方生成私钥b, 计算得到公钥 B=b∙G。并根据 i计算 K=B+iA ，将 K 发送给S 方。
S 方计算n个秘钥 K_j=a∙K−j∙a∙A，并对n个消息进行加密，将n个密文发送给R 方。
R 方只能对其中一个密文解密。
*/
class EccObliviousTransfer {
private:
    static void mpz_to_string(vector<mpz_class> &vec1, vector<string> &vec2) {
        for (int i = 0; i < vec1.size(); ++i) {
            string tmp = vec1[i].get_str();
            vec2[i] = tmp;
        }
    }

    static void string_to_mpz(vector<string> &vec1, vector<mpz_class> &vec2) {
        for (int i = 0; i < vec1.size(); ++i) {
            string tmp = vec1[i];
            vec2[i] = tmp;
        }
    }

public:
    ECC *ecc = new ECC();

    EccObliviousTransfer() {
        ecc->generate_point();
    }

    ~EccObliviousTransfer() {
        delete ecc;
    }

    vector<string> get_public_key();

    /*!
     * R 方生成私钥b, 计算得到公钥 B=b∙G
     * 并根据 i计算 K=B+iA ，将 K 发送给S 方
     *
     * @param A_public_key 发送方生成的公钥
     * @param i 接受选择的消息index
     * @return vector<string> 计算得出的k 值
     */
    vector<string> receiver_compute_k(vector<string> A_public_key, unsigned int i);

    /*!
     *  secret_key = a * B = b * A = a * b * G
     *
     * @param A_public_key 发送方生成公钥
     * @return 最终需要加密密钥值
     */
    string receiver_compute_secret_key(vector<string> &A_public_key);


    /*!
     * S 方计算n个秘钥 K_j=a∙K−j∙a∙A，并对n个消息进行加密，将n个密文发送给R 方。
     * @param msg_list  需要加密的信息列表 [m0,m1,m2 ...]
     * @param receiver_k  接收方计算得出得k值 [string0,string1]
     *
     *
     */
    vector<string> sender_compute_secret_list(vector<string> receiver_k, unsigned int msg_length);

    /*!
     * 计算全新的密钥 K_j=a∙K−j∙a∙A
     * @param B_random_k
     * @param i
     * @return
     */
    string sender_compute_secret_key(vector<string> &B_random_k, unsigned int i);

};


#endif //ECDH_ECC_OBLIVIOUS_TRANSFER_H
