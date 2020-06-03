#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "socket/tls/Socket.h"

namespace tls {

    Socket::Socket()
        : ::Socket()
        , ssl(0) {
    }


    bool Socket::startSSL(SSL_CTX* ctx) {
        this->ssl = SSL_new(ctx);
        SSL_set_fd(ssl, fd());
        err = SSL_accept(this->ssl);

        int sslerr = SSL_ERROR_NONE;
        if (err < 1) {
            sslerr = SSL_get_error(this->ssl, err);
        }

        return sslerr == SSL_ERROR_NONE;
        /*
             client_cert = SSL_get_peer_certificate (ssl);
             if (client_cert != NULL) {
                 printf ("Client certificate:\n");

                 str = X509_NAME_oneline (X509_get_subject_name (client_cert), 0,
           0); CHK_NULL(str); printf ("\t subject: %s\n", str); OPENSSL_free (str);

                 str = X509_NAME_oneline (X509_get_issuer_name  (client_cert), 0,
           0); CHK_NULL(str); printf ("\t issuer: %s\n", str); OPENSSL_free (str);

                 // We could do all sorts of certificate verification stuff here
           before deallocating the certificate.

                 X509_free (client_cert);
            } else {
                printf ("Client does not have certificate.\n");
            }
        */
    }


    void Socket::stopSSL() {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }


    ssize_t Socket::recv(void* buf, size_t len, int) {
        ssize_t ret = err;

        if (err > 0) {
            ret = ::SSL_read(ssl, buf, len);
        }

        return ret;
    }


    ssize_t Socket::send(const void* buf, size_t len, int) {
        ssize_t ret = err;

        if (err > 0) {
            ret = ::SSL_write(ssl, buf, len);
        }

        return ret;
    }

}; // namespace tls
