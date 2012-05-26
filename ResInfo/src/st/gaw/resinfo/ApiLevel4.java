package st.gaw.resinfo;

import android.annotation.TargetApi;

@TargetApi(4)
public class ApiLevel4 {

	public static String getBuildManufacturer() throws VerifyError {
		return android.os.Build.MANUFACTURER;
	}

}
