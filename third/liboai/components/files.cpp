#include "../include/components/files.h"

liboai::Response liboai::Files::list() const & noexcept(false) {
	Response res;
	res = this->Request(
		Method::HTTP_GET, "/files", "application/json",
		this->auth_.GetAuthorizationHeaders(),
		this->auth_.GetProxies(),
		this->auth_.GetProxyAuth(),
		this->auth_.GetMaxTimeout()
	);

	return res;
}

liboai::FutureResponse liboai::Files::list_async() const & noexcept(false) {
	return std::async(
		std::launch::async, [&]() -> liboai::Response {
			return this->Request(
				Method::HTTP_GET, "/files", "application/json",
				this->auth_.GetAuthorizationHeaders(),
				this->auth_.GetProxies(),
				this->auth_.GetProxyAuth(),
				this->auth_.GetMaxTimeout()
			);
		}
	);
}

liboai::Response liboai::Files::create(const std::filesystem::path& file, const std::string& purpose) const & noexcept(false) {
	if (!this->Validate(file)) {
		throw liboai::exception::OpenAIException(
			"File path provided is non-existent, is not a file, or is empty.",
			liboai::exception::EType::E_FILEERROR,
			"liboai::Files::create(...)"
		);
	}

	netimpl::components::Multipart form = {
		{ "purpose", purpose },
		{ "file", netimpl::components::File{file.generic_string()} }
	};
	
	Response res;
	res = this->Request(
		Method::HTTP_POST, "/files", "multipart/form-data",
		this->auth_.GetAuthorizationHeaders(),
		std::move(form),
		this->auth_.GetProxies(),
		this->auth_.GetProxyAuth(),
		this->auth_.GetMaxTimeout()
	);

	return res;
}

liboai::FutureResponse liboai::Files::create_async(const std::filesystem::path& file, const std::string& purpose) const & noexcept(false) {
	if (!this->Validate(file)) {
		throw liboai::exception::OpenAIException(
			"File path provided is non-existent, is not a file, or is empty.",
			liboai::exception::EType::E_FILEERROR,
			"liboai::Files::create_async(...)"
		);
	}

	netimpl::components::Multipart form = {
		{ "purpose", purpose },
		{ "file", netimpl::components::File{file.generic_string()} }
	};

	return std::async(
		std::launch::async, [&, form]() -> liboai::Response {
			return this->Request(
				Method::HTTP_POST, "/files", "multipart/form-data",
				this->auth_.GetAuthorizationHeaders(),
				std::move(form),
				this->auth_.GetProxies(),
				this->auth_.GetProxyAuth(),
				this->auth_.GetMaxTimeout()
			);
		}
	);
}

liboai::Response liboai::Files::remove(const std::string& file_id) const & noexcept(false) {
	Response res;
	res = this->Request(
		Method::HTTP_DELETE, "/files/" + file_id, "application/json",
		this->auth_.GetAuthorizationHeaders(),
		this->auth_.GetProxies(),
		this->auth_.GetProxyAuth(),
		this->auth_.GetMaxTimeout()
	);

	return res;
}

liboai::FutureResponse liboai::Files::remove_async(const std::string& file_id) const & noexcept(false) {
	return std::async(
		std::launch::async, [&]() -> liboai::Response {
			return this->Request(
				Method::HTTP_DELETE, "/files/" + file_id, "application/json",
				this->auth_.GetAuthorizationHeaders(),
				this->auth_.GetProxies(),
				this->auth_.GetProxyAuth(),
				this->auth_.GetMaxTimeout()
			);
		}
	);
}

liboai::Response liboai::Files::retrieve(const std::string& file_id) const & {
	Response res;
	res = this->Request(
		Method::HTTP_GET, "/files/" + file_id, "application/json",
		this->auth_.GetAuthorizationHeaders(),
		this->auth_.GetProxies(),
		this->auth_.GetProxyAuth(),
		this->auth_.GetMaxTimeout()
	);

	return res;
}

liboai::FutureResponse liboai::Files::retrieve_async(const std::string& file_id) const & noexcept(false) {
	return std::async(
		std::launch::async, [&]() -> liboai::Response {
			return this->Request(
				Method::HTTP_GET, "/files/" + file_id, "application/json",
				this->auth_.GetAuthorizationHeaders(),
				this->auth_.GetProxies(),
				this->auth_.GetProxyAuth(),
				this->auth_.GetMaxTimeout()
			);
		}
	);
}

bool liboai::Files::download(const std::string& file_id, const std::string& save_to) const & noexcept(false) {
	return Network::Download(
		save_to, ("https://api.openai.com/v1/files/" + file_id + "/content")
	);
}

std::future<bool> liboai::Files::download_async(const std::string& file_id, const std::string& save_to) const & noexcept(false) {
	return std::async(
		std::launch::async,
		&liboai::Network::Download, save_to, ("https://api.openai.com/v1/files/" + file_id + "/content")
	);
}