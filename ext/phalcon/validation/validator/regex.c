
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Validation\Validator\Regex
 *
 * Allows validate if the value of a field matches a regular expression
 *
 *<code>
 *use Phalcon\Validation\Validator\Regex as RegexValidator;
 *
 *$validator->add('created_at', new RegexValidator(array(
 *   'pattern' => '/^[0-9]{4}[-\/](0[1-9]|1[12])[-\/](0[1-9]|[12][0-9]|3[01])$/',
 *   'message' => 'The creation date is invalid'
 *)));
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Validation_Validator_Regex) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Validation\\Validator, Regex, phalcon, validation_validator_regex, phalcon_validation_validator_ce, phalcon_validation_validator_regex_method_entry, 0);

	zend_class_implements(phalcon_validation_validator_regex_ce TSRMLS_CC, 1, phalcon_validation_validatorinterface_ce);
	return SUCCESS;

}

/**
 * Executes the validation
 *
 * @param  Phalcon\Validation validation
 * @param  string field
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Validator_Regex, validate) {

	zephir_nts_static zephir_fcall_cache_entry *_8 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool failed, _2;
	zval *validation, *field, *matches, *message = NULL, *value = NULL, *label = NULL, *replacePairs, *_0 = NULL, *_1, *_3 = NULL, *_4, *_5, *_6, *_7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &validation, &field);



	if (!(zephir_instance_of_ev(validation, phalcon_validation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'validation' must be an instance of 'Phalcon\\Validation'");
		return;
	}
	ZEPHIR_INIT_VAR(matches);
	ZVAL_NULL(matches);
	ZEPHIR_CALL_METHOD(&value, validation, "getvalue", NULL, field);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "allowEmpty", 0);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issetoption", NULL, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	_2 = zephir_is_true(_0);
	if (_2) {
		_2 = ZEPHIR_IS_EMPTY(value);
	}
	if (_2) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_INIT_BNVAR(_1);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "pattern", 0);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getoption", NULL, _4);
	zephir_check_temp_parameter(_4);
	zephir_check_call_status();
	zephir_preg_match(_1, &(_1), _3, value, matches, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_1)) {
		zephir_array_fetch_long(&_5, matches, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		failed = !ZEPHIR_IS_EQUAL(_5, value);
	} else {
		failed = 1;
	}
	if (failed == 1) {
		ZEPHIR_INIT_BNVAR(_1);
		ZVAL_STRING(_1, "label", 0);
		ZEPHIR_CALL_METHOD(&label, this_ptr, "getoption", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		if (ZEPHIR_IS_EMPTY(label)) {
			ZEPHIR_CALL_METHOD(&label, validation, "getlabel", NULL, field);
			zephir_check_call_status();
			if (ZEPHIR_IS_EMPTY(label)) {
				ZEPHIR_CPY_WRT(label, field);
			}
		}
		ZEPHIR_INIT_BNVAR(_1);
		ZVAL_STRING(_1, "message", 0);
		ZEPHIR_CALL_METHOD(&message, this_ptr, "getoption", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(replacePairs);
		array_init_size(replacePairs, 2);
		zephir_array_update_string(&replacePairs, SL(":field"), &label, PH_COPY | PH_SEPARATE);
		if (ZEPHIR_IS_EMPTY(message)) {
			ZEPHIR_INIT_BNVAR(_1);
			ZVAL_STRING(_1, "Regex", 0);
			ZEPHIR_CALL_METHOD(&message, validation, "getdefaultmessage", NULL, _1);
			zephir_check_temp_parameter(_1);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(_6);
		object_init_ex(_6, phalcon_validation_message_ce);
		ZEPHIR_CALL_FUNCTION(&_7, "strtr", &_8, message, replacePairs);
		zephir_check_call_status();
		ZEPHIR_INIT_BNVAR(_1);
		ZVAL_STRING(_1, "Regex", 0);
		ZEPHIR_CALL_METHOD(NULL, _6, "__construct", NULL, _7, field, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, validation, "appendmessage", NULL, _6);
		zephir_check_call_status();
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

