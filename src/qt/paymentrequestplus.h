// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The GIANT developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PAYMENTREQUESTPLUS_H
#define BITCOIN_QT_PAYMENTREQUESTPLUS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "paymentrequest.pb.h"
#pragma GCC diagnostic pop

#include "base58.h"

#include <openssl/x509.h>

#include <QByteArray>
#include <QList>
#include <QString>

//
// Wraps dumb protocol buffer paymentRequest
// with extra methods
//

class PaymentRequestPlus
{
public:
    PaymentRequestPlus() {}

    bool parse(const QByteArray& data);
    bool SerializeToString(std::string* output) const;

    bool IsInitialized() const;
    QString getPKIType() const;
    // Returns true if merchant's identity is authenticated, and
    // returns human-readable merchant identity in merchant
    bool getMerchant(X509_STORE* certStore, QString& merchant) const;

    // Returns list of outputs, amount
    QList<std::pair<CScript, CAmount> > getPayTo() const;

    const payments::PaymentDetails& getDetails() const { return details; }

private:
    payments::PaymentRequest paymentRequest;
    payments::PaymentDetails details;
};

#endif // BITCOIN_QT_PAYMENTREQUESTPLUS_H
