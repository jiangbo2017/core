# -*- Mode: makefile-gmake; tab-width: 4; indent-tabs-mode: t -*-
#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

$(eval $(call gb_ExternalProject_ExternalProject,libstaroffice))

$(eval $(call gb_ExternalProject_use_autoconf,libstaroffice,build))

$(eval $(call gb_ExternalProject_register_targets,libstaroffice,\
	build \
))

$(eval $(call gb_ExternalProject_use_externals,libstaroffice,\
	revenge \
))

$(call gb_ExternalProject_get_state_target,libstaroffice,build) :
	$(call gb_ExternalProject_run,build,\
		export PKG_CONFIG="" \
		&& ./configure \
			--with-pic \
			$(if $(DISABLE_DYNLOADING), \
				--enable-static --disable-shared \
			, \
				--enable-shared --disable-static \
			) \
			--with-sharedptr=c++11 \
			--without-docs \
			--disable-tools \
			--disable-zip \
			$(if $(ENABLE_DEBUG),--enable-debug,--disable-debug) \
			$(if $(verbose),--disable-silent-rules,--enable-silent-rules) \
			--disable-werror \
			CXXFLAGS="$(CXXFLAGS) $(CXXFLAGS_CXX11)" \
			$(if $(filter LINUX,$(OS)),$(if $(SYSTEM_REVENGE),, \
				'LDFLAGS=-Wl$(COMMA)-z$(COMMA)origin \
					-Wl$(COMMA)-rpath$(COMMA)\$$$$ORIGIN')) \
			$(if $(CROSS_COMPILING),--build=$(BUILD_PLATFORM) --host=$(HOST_PLATFORM)) \
			$(if $(filter MACOSX,$(OS)),--prefix=/@.__________________________________________________OOO) \
		&& (cd $(EXTERNAL_WORKDIR)/src/lib && \
			$(MAKE)) \
		$(if $(filter MACOSX,$(OS)),\
			&& $(PERL) $(SRCDIR)/solenv/bin/macosx-change-install-names.pl shl OOO \
				$(EXTERNAL_WORKDIR)/src/lib/.libs/libstaroffice-0.0.0.dylib \
		) \
	)

# vim: set noet sw=4 ts=4:
