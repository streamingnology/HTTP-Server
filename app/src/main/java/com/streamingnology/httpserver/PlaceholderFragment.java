/******************************************************************************
 |
 | Copyright (c) 2018 streamingnology Inc (https://github.com/streamingnology)
 |
 | This file is part of HTTP Server
 |
 | Permission is hereby granted, free of charge, to any person obtaining a copy
 | of this software and associated documentation files (the "Software"), to deal
 | in the Software without restriction, including without limitation the rights
 | to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 | copies of the Software, and to permit persons to whom the Software is
 | furnished to do so, subject to the following conditions:
 |
 | The above copyright notice and this permission notice shall be included in all
 | opies or substantial portions of the Software.
 |
 | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 | MPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 | FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 | AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 | LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 | OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 | OFTWARE.
 ******************************************************************************/

package com.streamingnology.httpserver;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

import lib.folderpicker.FolderPicker;

import static android.content.Context.MODE_PRIVATE;


public class PlaceholderFragment extends Fragment {
  private static final int SDCARD_PERMISSION_FOLDER = 12,
          SDCARD_PERMISSION_FILE = 123,
          FOLDER_PICKER_CODE = 78,
          FILE_PICKER_CODE = 786;
  private static String ARG_SECTION_NUMBER = "section_number";
  private String PREFS_NAME = "UserSettings";
  private String PREFS_ROOT = "webroot";
  private String PREFS_PORT = "listenport";
  private String serverroot = "/storage/emulated/0";
  private int    serverport = 8080;
  private static HTTPServer httpServer = null;
  private TextView textViewTestUri;
  private TextView textViewWebRoot;
  private EditText editTextListenport;
  private Button   buttonStart;
  private Button   buttonStop;
  private TextView textViewStatusContent;
  private Context  context;

  private AdView adView;

  public PlaceholderFragment() {
  }

  @Override
  public void onHiddenChanged(boolean hidden) {
    super.onHiddenChanged(hidden);
  }

  public void setContext(Context context) {
    this.context = context;
  }

  /**
   * Returns a new instance of this fragment for the given section
   * number.
   */
  static public PlaceholderFragment newInstance(int sectionNumber, Context context) {
    PlaceholderFragment fragment = new PlaceholderFragment();
    Bundle args = new Bundle();
    args.putInt(ARG_SECTION_NUMBER, sectionNumber);
    fragment.setArguments(args);
    fragment.setContext(context);
    return fragment;
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container,
                           Bundle savedInstanceState) {
    int i = getArguments().getInt(ARG_SECTION_NUMBER);
    View rootView;
    if (i == 1) {
      rootView = inflater.inflate(R.layout.fragment_mainpage, container, false);
      buttonStart = rootView.findViewById(R.id.start);
      buttonStart.setOnClickListener(onClickListener);
      buttonStop = rootView.findViewById(R.id.stop);
      buttonStop.setOnClickListener(onClickListener);
      textViewStatusContent = rootView.findViewById(R.id.statuscontent);
      textViewTestUri = rootView.findViewById(R.id.testuri);
      updateStatus();
      showUserSettings();
      showTestUri();
    } else if (i == 2) {
      rootView = inflater.inflate(R.layout.fragment_settings, container, false);
      textViewWebRoot = rootView.findViewById(R.id.webroot2);
      textViewWebRoot.setClickable(true);
      textViewWebRoot.setOnClickListener(onWebRootClickListener);
      editTextListenport = rootView.findViewById(R.id.listenport);
      editTextListenport.setOnEditorActionListener(new TextView.OnEditorActionListener() {
        @Override
        public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
          saveUserSettings();
          return false;
        }
      });
      editTextListenport.setOnFocusChangeListener(new TextView.OnFocusChangeListener() {

        @Override
        public void onFocusChange(View v, boolean hasFocus) {
          saveUserSettings();
        }
      });
      showUserSettings();
    } else if (i == 3) {
      rootView = inflater.inflate(R.layout.fragment_about, container, false);
    } else {
      rootView = inflater.inflate(R.layout.fragment_about, container, false);
    }

    adView = rootView.findViewById(R.id.ad_view);
    AdRequest adRequest = new AdRequest.Builder().build();
    adView.loadAd(adRequest);

    return rootView;
  }

  /** Called when leaving the activity */
  @Override
  public void onPause() {
    if (adView != null) {
      adView.pause();
    }
    super.onPause();
  }

  /** Called when returning to the activity */
  @Override
  public void onResume() {
    super.onResume();
    if (adView != null) {
      adView.resume();
    }
  }

  /** Called before the activity is destroyed */
  @Override
  public void onDestroy() {
    if (adView != null) {
      adView.destroy();
    }
    super.onDestroy();
  }

  private View.OnClickListener onClickListener = new View.OnClickListener() {
    @Override
    public void onClick(View view) {
      switch (view.getId()) {
        case R.id.start: {
          if (httpServer == null) {
            showUserSettings();
            httpServer = new HTTPServer();
            httpServer.setParameter(serverroot, serverport);
            httpServer.open();
            int result = httpServer.start();
            if (result != 0) {
              String err = httpServer.getErrorMessage();
              AlertDialog.Builder alertDialogBuilder=new AlertDialog.Builder(context);
              AlertDialog alertDialog = alertDialogBuilder.create();
              alertDialog.setMessage(err);
              alertDialog.show();

              httpServer.stop();
              httpServer = null;
            } else {
              showTestUri();
              saveUserSettings();
              updateStatus();
            }
          }
          break;
        }
        case R.id.stop: {
          if (httpServer != null) {
            httpServer.stop();
            httpServer = null;
          }
          updateStatus();
          break;
        }
        default: {
          break;
        }
      }
    }
  };

  private TextView.OnClickListener onWebRootClickListener = new TextView.OnClickListener() {

    @Override
    public void onClick(View v) {
      Intent intent = new Intent(context, FolderPicker.class);
      startActivityForResult(intent, FOLDER_PICKER_CODE);
    }
  };

  public void onActivityResult(int requestCode, int resultCode, Intent intent) {
    if (requestCode == FOLDER_PICKER_CODE && resultCode == Activity.RESULT_OK) {
      String folderLocation = intent.getExtras().getString("data");
      textViewWebRoot.setText(folderLocation);
      saveUserSettings();
    }
  }

  private void saveUserSettings() {
    SharedPreferences userSettings = context.getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
    SharedPreferences.OnSharedPreferenceChangeListener changeListener = new SharedPreferences.OnSharedPreferenceChangeListener() {

      @Override
      public void onSharedPreferenceChanged(SharedPreferences preferences, String key) {
      }
    };
    userSettings.registerOnSharedPreferenceChangeListener(changeListener);
    SharedPreferences.Editor editor = userSettings.edit();
    if (textViewWebRoot != null) {
      String root = textViewWebRoot.getText().toString();
      if (!root.isEmpty()) {
        editor.putString(PREFS_ROOT, root);
      }
    }
    if (editTextListenport != null) {
      try {
        int port = Integer.parseInt(editTextListenport.getText().toString());
        if (port <= 0 || port >=65535) {
          port = 8080;
          editTextListenport.setText(String.valueOf(port));
          AlertDialog.Builder alertDialogBuilder=new AlertDialog.Builder(context);
          AlertDialog alertDialog = alertDialogBuilder.create();
          alertDialog.setMessage("Invalid Port, please input number between 0 and 65535");
          alertDialog.show();
        }
        editor.putInt(PREFS_PORT, port);
      } catch (Exception e) {

      }
    }
    editor.apply();
  }

  private void showUserSettings() {
    SharedPreferences userSettings = context.getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
    String root = userSettings.getString(PREFS_ROOT, serverroot);
    int    port = userSettings.getInt(PREFS_PORT, serverport);
    serverroot = root;
    serverport = port;
    if (textViewWebRoot != null) {
      textViewWebRoot.setText(root);
    }
    if (editTextListenport != null) {
      editTextListenport.setText(String.valueOf(port));
    }
  }

  private void showTestUri() {
    if (textViewTestUri != null) {
      String ip = GetIPAddressUtil.getWifiIP(context);
      if (ip == null) {
        ip = "127.0.0.1";
      }
      String testuri = "http://" + ip + ":" + String.valueOf(serverport);
      textViewTestUri.setText(testuri);
    }
  }

  private void updateStatus() {
    if (httpServer == null) {
      buttonStart.setEnabled(true);
      buttonStop.setEnabled(false);
      textViewStatusContent.setTextColor(Color.RED);
      textViewStatusContent.setText(R.string.stopped);
    } else {
      buttonStart.setEnabled(false);
      buttonStop.setEnabled(true);
      textViewStatusContent.setTextColor(Color.GREEN);
      textViewStatusContent.setText(R.string.running);
    }
  }

}
