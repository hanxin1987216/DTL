#
# Configuration file for test
# Author: han.xin@datatom.com
#

####################################################################################################

TEST_ENV = $(DTSRC)/test_env/$(BUILD)/$(CPU)
TEST_ENV_LOCALE = $(TEST_ENV)/locale
TEST_ENV_IMAGES = $(TEST_ENV)/images
TEST_ENV_COMPONENTS = $(TEST_ENV)/components


check_test_dir:
	@test -z "$(TEST_ENV)" || mkdir -p -- "$(TEST_ENV)"
	@test -z "$(TEST_ENV_LOCALE)" || mkdir -p -- "$(TEST_ENV_LOCALE)"
	@test -z "$(TEST_ENV_IMAGES)" || mkdir -p -- "$(TEST_ENV_IMAGES)"
	@test -z "$(TEST_ENV_COMPONENTS)" || mkdir -p -- "$(TEST_ENV_COMPONENTS)"
	
copy_config_files: $(CONFIG_FILES)
ifneq ("$(CONFIG_FILES)", "$(DEF_MO_NOT_EXITS)")
	@-$(foreach n,$(CONFIG_FILES),cp -rf $(n) $(TEST_ENV)/$(notdir $(n));)
ifneq ("$(CUSTOM_COPY_PATH)", "")
	@-$(foreach n,$(CONFIG_FILES),cp -rf $(TEST_ENV)/$(notdir $(n)) $(CUSTOM_COPY_PATH);)
endif
endif

copy_test_files:
ifneq ("$(CUSTOM_COPY_PATH)", "")
ifeq ("$(TARGET_TYPE)", "component")
	@-cp -rf $(LIBFILE)		$(CUSTOM_COPY_PATH_COMPONENTS)
else
	@-cp -rf $(LIBFILE)		$(CUSTOM_COPY_PATH)
endif

	@(test -d $(RES_PATH) && cp -rf $(RES_PATH)/*	$(CUSTOM_COPY_PATH_LOCALE)) || exit 0
	@(test -d ./images && cp -rf ./images/*		$(CUSTOM_COPY_PATH_IMAGES)) || exit 0
endif
ifeq ("$(TARGET_TYPE)", "component")
	@-cp -rf $(LIBFILE)		$(TEST_ENV_COMPONENTS)
else
	@-cp -rf $(LIBFILE)		$(TEST_ENV)
endif

	@(test -d $(RES_PATH) && cp -rf $(RES_PATH)/*	$(TEST_ENV_LOCALE)) || exit 0
	@(test -d ./images && cp -rf ./images/*		$(TEST_ENV_IMAGES)) || exit 0
