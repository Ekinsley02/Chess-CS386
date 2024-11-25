import unittest
import subprocess
import time
import pyautogui

class TestUserLogin(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        # Start the Pygame application as a subprocess and capture its output
        cls.process = subprocess.Popen(
            ["python", "main.py"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        time.sleep(5)  # Wait for the application to start

    @classmethod
    def tearDownClass(cls):
        # Capture any remaining output from the Pygame application
        stdout, stderr = cls.process.communicate()
        if stdout:
            print("Application stdout:\n", stdout)
        if stderr:
            print("Application stderr:\n", stderr)

        # Terminate the Pygame subprocess
        cls.process.terminate()
        cls.process.wait()

    def test_valid_login(self):
        try:
            # Assuming the Pygame window is up, click the login box
            # You might need to adjust the coordinates depending on where the login box is located

            # Coordinates (x, y) should be relative to where the username box appears in the Pygame window.
            username_box_coords = (400, 300)  # Replace with actual coordinates of the username box
            password_box_coords = (400, 350)  # Replace with actual coordinates of the password box

            # Click on the username box and type the username
            pyautogui.click(*username_box_coords)
            time.sleep(0.5)
            pyautogui.write("valid_user", interval=0.1)

            # Click on the password box and type the password
            pyautogui.click(*password_box_coords)
            time.sleep(0.5)
            pyautogui.write("valid_password", interval=0.1)

            # Press Enter to submit or click the login button if available
            pyautogui.press('enter')

            # Wait for the login process to complete
            time.sleep(5)

            # Check if the application did not crash
            return_code = self.process.poll()

            # Expecting return code to be either None (still running) or 0 (terminated normally)
            if return_code is not None:
                self.assertEqual(return_code, 0, f"The application exited unexpectedly with code {return_code}.")
        
        except Exception as e:
            print(f"Exception occurred during test_valid_login: {e}")

    def test_invalid_login(self):
        try:
            # Click the username box and enter invalid username
            username_box_coords = (400, 300)  # Replace with actual coordinates of the username box
            password_box_coords = (400, 350)  # Replace with actual coordinates of the password box

            # Click on the username box and type the username
            pyautogui.click(*username_box_coords)
            time.sleep(0.5)
            pyautogui.write("invalid_user", interval=0.1)

            # Click on the password box and type the password
            pyautogui.click(*password_box_coords)
            time.sleep(0.5)
            pyautogui.write("invalid_password", interval=0.1)

            # Press Enter to submit or click the login button if available
            pyautogui.press('enter')

            # Wait for the login process to complete
            time.sleep(5)

            # Check if the application did not crash
            return_code = self.process.poll()

            # Expecting return code to be either None (still running) or 0 (terminated normally)
            if return_code is not None:
                self.assertEqual(return_code, 0, f"The application exited unexpectedly with code {return_code}.")
        
        except Exception as e:
            print(f"Exception occurred during test_invalid_login: {e}")

if __name__ == "__main__":
    unittest.main()
